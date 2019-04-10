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
     TEMPLATE_DELETE = 330,
     SPF_ANALYSIS = 331,
     SPF_PARALLEL = 332,
     SPF_TRANSFORM = 333,
     SPF_NOINLINE = 334,
     SPF_PARALLEL_REG = 335,
     SPF_END_PARALLEL_REG = 336,
     SPF_PRIVATES_EXPANSION = 337,
     SPF_FISSION = 338,
     BINARY_OP = 341,
     UNARY_OP = 342
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
#define TEMPLATE_DELETE 330
#define SPF_ANALYSIS 331
#define SPF_PARALLEL 332
#define SPF_TRANSFORM 333
#define SPF_NOINLINE 334
#define SPF_PARALLEL_REG 335
#define SPF_END_PARALLEL_REG 336
#define SPF_PRIVATES_EXPANSION 337
#define SPF_FISSION 338
#define BINARY_OP 341
#define UNARY_OP 342




/* Copy the first part of user declarations.  */
#line 340 "gram1.y"

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
#line 421 "gram1.y"
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
#line 873 "gram1.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 625 "gram1.y"

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
#line 1029 "gram1.tab.c"

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
#define YYLAST   5543

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  343
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  519
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1253
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2468

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

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
     332,   333,   334,   335,   336,   337,   338,   339,   340,     1,
       2,   341,   342
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
    2141,  2143,  2145,  2147,  2149,  2153,  2157,  2160,  2164,  2166,
    2170,  2172,  2176,  2178,  2182,  2184,  2189,  2193,  2195,  2199,
    2201,  2205,  2210,  2212,  2217,  2222,  2227,  2231,  2235,  2237,
    2241,  2245,  2247,  2251,  2255,  2257,  2261,  2265,  2267,  2271,
    2272,  2278,  2285,  2294,  2296,  2300,  2302,  2304,  2306,  2311,
    2313,  2314,  2317,  2321,  2324,  2329,  2330,  2332,  2338,  2343,
    2350,  2355,  2357,  2362,  2367,  2369,  2376,  2378,  2382,  2384,
    2388,  2390,  2395,  2397,  2399,  2403,  2405,  2407,  2411,  2413,
    2414,  2416,  2419,  2423,  2425,  2428,  2434,  2439,  2444,  2451,
    2453,  2457,  2459,  2461,  2468,  2473,  2475,  2479,  2481,  2483,
    2485,  2487,  2489,  2493,  2495,  2497,  2499,  2506,  2511,  2513,
    2518,  2520,  2522,  2524,  2526,  2531,  2534,  2542,  2544,  2549,
    2551,  2553,  2565,  2566,  2569,  2573,  2575,  2579,  2581,  2585,
    2587,  2591,  2593,  2597,  2599,  2603,  2605,  2609,  2618,  2620,
    2624,  2627,  2630,  2638,  2640,  2644,  2646,  2650,  2652,  2657,
    2659,  2663,  2665,  2667,  2668,  2670,  2672,  2675,  2677,  2679,
    2681,  2683,  2685,  2687,  2689,  2691,  2693,  2695,  2704,  2711,
    2720,  2727,  2729,  2736,  2743,  2750,  2757,  2759,  2763,  2769,
    2771,  2775,  2784,  2791,  2798,  2803,  2809,  2815,  2818,  2821,
    2822,  2824,  2828,  2830,  2835,  2843,  2845,  2849,  2853,  2855,
    2859,  2865,  2869,  2873,  2875,  2879,  2881,  2883,  2887,  2891,
    2895,  2899,  2910,  2919,  2930,  2931,  2932,  2934,  2937,  2942,
    2947,  2954,  2956,  2958,  2960,  2962,  2964,  2966,  2968,  2970,
    2972,  2974,  2976,  2983,  2988,  2993,  2997,  3007,  3009,  3011,
    3015,  3017,  3023,  3029,  3039,  3040,  3042,  3044,  3048,  3052,
    3056,  3060,  3064,  3071,  3075,  3079,  3083,  3087,  3095,  3101,
    3103,  3105,  3109,  3114,  3116,  3118,  3122,  3124,  3126,  3130,
    3134,  3137,  3141,  3146,  3151,  3157,  3163,  3165,  3168,  3173,
    3178,  3183,  3184,  3186,  3189,  3197,  3204,  3208,  3212,  3220,
    3226,  3228,  3232,  3234,  3239,  3242,  3246,  3250,  3255,  3262,
    3266,  3269,  3273,  3275,  3277,  3282,  3288,  3292,  3299,  3302,
    3307,  3310,  3312,  3316,  3320,  3321,  3323,  3327,  3330,  3333,
    3336,  3339,  3349,  3355,  3357,  3361,  3364,  3367,  3370,  3380,
    3385,  3387,  3391,  3393,  3395,  3398,  3399,  3407,  3409,  3414,
    3416,  3420,  3422,  3424,  3426,  3443,  3444,  3448,  3452,  3456,
    3460,  3467,  3477,  3483,  3485,  3489,  3495,  3497,  3501,  3503,
    3505,  3507,  3509,  3511,  3513,  3515,  3517,  3519,  3521,  3523,
    3525,  3527,  3529,  3531,  3533,  3535,  3537,  3539,  3541,  3543,
    3545,  3547,  3549,  3551,  3553,  3555,  3558,  3561,  3566,  3570,
    3575,  3581,  3583,  3585,  3587,  3589,  3591,  3593,  3595,  3597,
    3599,  3605,  3608,  3611,  3614,  3617,  3620,  3626,  3628,  3630,
    3632,  3637,  3642,  3647,  3652,  3654,  3656,  3658,  3660,  3662,
    3664,  3666,  3668,  3670,  3672,  3674,  3676,  3678,  3680,  3682,
    3687,  3691,  3696,  3702,  3704,  3706,  3708,  3710,  3715,  3719,
    3722,  3727,  3731,  3736,  3740,  3745,  3751,  3753,  3755,  3757,
    3759,  3761,  3763,  3765,  3773,  3779,  3781,  3783,  3785,  3787,
    3792,  3796,  3801,  3807,  3809,  3811,  3816,  3820,  3825,  3831,
    3833,  3835,  3838,  3840,  3843,  3848,  3852,  3857,  3861,  3866,
    3872,  3874,  3876,  3878,  3880,  3882,  3884,  3886,  3888,  3890,
    3892,  3894,  3897,  3902,  3906,  3909,  3914,  3918,  3921,  3925,
    3928,  3931,  3934,  3937,  3940,  3943,  3947,  3950,  3956,  3959,
    3965,  3968,  3974,  3976,  3978,  3982,  3986,  3987,  3988,  3990,
    3992,  3994,  3996,  3998,  4000,  4004,  4007,  4013,  4018,  4021,
    4027,  4032,  4035,  4038,  4040,  4042,  4046,  4049,  4052,  4055,
    4060,  4065,  4070,  4075,  4080,  4085,  4087,  4089,  4091,  4095,
    4098,  4101,  4103,  4105,  4107,  4109,  4111,  4113,  4115,  4120,
    4125,  4130,  4133,  4135,  4137,  4141,  4143,  4145,  4151,  4157,
    4159,  4163,  4165,  4167,  4169,  4175,  4181,  4187,  4189,  4193,
    4196,  4202,  4205,  4211
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     344,     0,    -1,    -1,   344,   345,   116,    -1,   346,   347,
     563,    -1,   346,   364,   563,    -1,   346,   509,   563,    -1,
     346,   133,   360,    -1,   346,   247,    -1,   257,    -1,     1,
      -1,   150,    -1,   193,   348,   355,    -1,    57,   348,   356,
      -1,   233,   348,   350,   357,    -1,   349,   233,   348,   350,
     357,    -1,   124,   348,   351,   357,   353,    -1,   352,   357,
     353,    -1,   114,   354,   357,   353,    -1,   164,   348,   354,
      -1,    -1,   202,   361,    -1,   195,   361,    -1,    95,   361,
      -1,   354,    -1,   354,    -1,   385,   124,   348,   354,    -1,
     385,   349,   124,   348,   354,    -1,   349,   124,   348,   354,
      -1,   349,   385,   124,   348,   354,    -1,   361,   362,    -1,
     361,   213,    15,   354,    21,    -1,   129,    -1,    -1,   354,
      -1,    -1,   354,    -1,    -1,    15,    21,    -1,    15,   358,
      21,    -1,   359,    -1,   358,     8,   359,    -1,   354,    -1,
       5,    -1,    64,    -1,    -1,    -1,    -1,   369,    -1,   370,
      -1,   371,    -1,   401,    -1,   397,    -1,   564,    -1,   406,
      -1,   407,    -1,   408,    -1,   466,    -1,   387,    -1,   402,
      -1,   412,    -1,   216,   476,    -1,   216,   476,   477,   443,
      -1,   123,   475,    -1,   183,   476,    15,   449,    21,    -1,
     377,    -1,   378,    -1,   383,    -1,   380,    -1,   382,    -1,
     398,    -1,   399,    -1,   400,    -1,   365,    -1,   453,    -1,
     451,    -1,   379,    -1,   142,   476,    -1,   142,   476,   354,
      -1,   141,   476,    15,   367,    21,    -1,   140,   476,    15,
      26,    21,    -1,   107,   518,    -1,    10,    -1,   366,    -1,
     368,    -1,    17,    -1,    16,    -1,     5,    -1,     9,    -1,
      37,    -1,    23,    -1,    22,    -1,    35,    -1,    38,    -1,
      34,    -1,    25,    -1,    32,    -1,    29,    -1,    28,    -1,
      31,    -1,    30,    -1,    33,    -1,    24,    -1,   245,   476,
     477,   354,    -1,   245,     8,   476,   361,   376,   477,   354,
      -1,   112,   476,    -1,   112,   476,   354,    -1,   385,   372,
     354,   476,   459,   391,   396,    -1,   371,     8,   354,   459,
     391,   396,    -1,    -1,     7,     7,    -1,     8,   361,   373,
       7,     7,    -1,   374,    -1,   373,     8,   361,   374,    -1,
     183,    -1,   376,    -1,    44,    -1,    87,   459,    -1,   119,
      -1,   145,    15,   375,    21,    -1,   143,    -1,   178,    -1,
     187,    -1,   216,    -1,   230,    -1,   236,    -1,   361,   148,
      -1,   361,   180,    -1,   361,   147,    -1,   194,    -1,   191,
      -1,   145,   476,    15,   375,    21,   477,   354,    -1,   377,
       8,   354,    -1,   178,   476,   477,   354,    -1,   378,     8,
     354,    -1,   230,   476,   477,   405,    -1,   379,     8,   405,
      -1,   191,   476,    -1,   191,   476,   477,   381,   445,    -1,
      -1,   219,   476,    -1,   194,   476,    -1,   194,   476,   477,
     384,   445,    -1,    -1,   389,   386,   393,   386,    -1,   244,
      15,   354,    21,   386,    -1,    -1,   388,   354,    -1,   387,
       8,   354,    -1,    13,    -1,     6,    -1,   390,    -1,   144,
      -1,   200,    -1,    68,    -1,    90,    -1,    91,    -1,   154,
      -1,    63,    -1,    -1,   392,    -1,     5,   539,   496,   540,
     386,    -1,     5,   539,    15,   540,     5,    21,    -1,     5,
     539,    15,   540,   482,    21,    -1,    -1,   392,    -1,    15,
     559,   394,   395,    21,    -1,    15,   559,   394,   395,     8,
     559,   394,   395,    21,    -1,   482,    -1,     5,    -1,   550,
     482,    -1,   550,     5,    -1,    -1,    -1,    26,   482,    -1,
      18,   482,    -1,    87,   477,   476,   354,   459,    -1,   397,
       8,   354,   459,    -1,    44,   476,   477,   405,    -1,   398,
       8,   405,    -1,   187,   476,   477,   405,    -1,   399,     8,
     405,    -1,   236,   476,   477,   405,    -1,   400,     8,   405,
      -1,    67,   476,   405,    -1,    67,   476,   404,   405,    -1,
     401,   533,   404,   533,   405,    -1,   401,     8,   405,    -1,
     167,   476,   403,   485,    -1,   402,   533,   403,   533,   485,
      -1,   402,     8,   485,    -1,    37,   354,    37,    -1,    23,
      -1,    37,   354,    37,    -1,   354,   459,    -1,   119,   476,
     477,   354,    -1,   406,     8,   354,    -1,   143,   476,   477,
     354,    -1,   407,     8,   354,    -1,   117,   476,   409,    -1,
     408,     8,   409,    -1,    15,   410,    21,    -1,   411,     8,
     411,    -1,   410,     8,   411,    -1,   354,    -1,   354,    15,
     481,    21,    -1,   490,    -1,   413,    -1,    80,   475,   414,
     416,    -1,   413,   533,   416,    -1,    -1,    -1,   417,    37,
     418,    37,    -1,   419,    -1,   417,     8,   419,    -1,   430,
      -1,   418,     8,   430,    -1,   420,   422,    -1,   420,   422,
     423,    -1,   420,   422,   424,    -1,   420,   422,   423,   424,
      -1,   420,   427,    -1,    -1,   354,    -1,   354,    -1,    15,
     425,    21,    -1,    15,   426,     7,   426,    21,    -1,   439,
      -1,   425,     8,   439,    -1,    -1,   439,    -1,    15,   428,
       8,   421,    26,   425,    21,    -1,   429,    -1,   428,     8,
     429,    -1,   422,   423,    -1,   422,   424,    -1,   422,   423,
     424,    -1,   427,    -1,   431,    -1,   420,   421,     5,   431,
      -1,   434,     5,   431,    -1,   420,   421,    -1,   433,    -1,
     435,    -1,   437,    -1,    36,    -1,    36,   246,   499,    -1,
      27,    -1,    27,   246,   499,    -1,    64,    -1,   432,    -1,
     420,   485,    15,   559,   478,    21,    -1,    59,    -1,   434,
      -1,    17,   434,    -1,    16,   434,    -1,   149,    -1,   149,
     246,   499,    -1,   436,    -1,    17,   436,    -1,    16,   436,
      -1,   201,    -1,   201,   246,   499,    -1,    92,    -1,    92,
     246,   499,    -1,    15,   438,     8,   438,    21,    -1,   435,
      -1,   433,    -1,   440,    -1,    17,   440,    -1,    16,   440,
      -1,   439,    17,   440,    -1,   439,    16,   440,    -1,   441,
      -1,   440,     5,   441,    -1,   440,    37,   441,    -1,   442,
      -1,   442,     9,   441,    -1,   149,    -1,   421,    -1,    15,
     439,    21,    -1,   444,    -1,   443,     8,   444,    -1,   405,
      -1,   404,    -1,   446,   448,   447,    -1,   445,     8,   446,
     448,   447,    -1,    -1,    -1,   354,    -1,   177,    15,   367,
      21,    -1,    47,    15,    26,    21,    -1,   450,    -1,   449,
       8,   450,    -1,   354,    26,   482,    -1,   163,   452,    -1,
     354,    -1,   452,     8,   354,    -1,   248,   476,   454,    -1,
     248,   476,   454,     8,   363,   457,    -1,   248,   476,   454,
       8,   363,   172,    -1,   248,   476,   454,     8,   363,   172,
     455,    -1,   354,    -1,   456,    -1,   455,     8,   456,    -1,
     354,    18,   354,    -1,   354,    -1,   458,    -1,   457,     8,
     458,    -1,   354,    18,   354,    -1,    -1,    15,   460,    21,
      -1,    -1,   461,   462,    -1,   460,     8,   462,    -1,   463,
      -1,     7,    -1,   482,     7,    -1,   482,     7,   463,    -1,
       5,    -1,   482,    -1,   465,    -1,   464,     8,   465,    -1,
     149,    -1,   130,   476,   467,    -1,   131,    -1,   468,    -1,
     467,     8,   468,    -1,   469,    15,   472,    21,    -1,    -1,
     470,   471,    -1,   231,   390,    -1,   385,    -1,   473,    -1,
     472,     8,   473,    -1,   474,    -1,   474,    16,   474,    -1,
     129,    -1,    -1,    -1,    -1,     7,     7,    -1,    -1,   480,
      -1,   482,    -1,   500,    -1,   550,   482,    -1,   559,   479,
      -1,   480,     8,   559,   479,    -1,   482,    -1,   481,     8,
     482,    -1,   483,    -1,    15,   482,    21,    -1,   498,    -1,
     486,    -1,   494,    -1,   501,    -1,   482,    17,   482,    -1,
     482,    16,   482,    -1,   482,     5,   482,    -1,   482,    37,
     482,    -1,   482,     9,   482,    -1,   366,   482,    -1,    17,
     482,    -1,    16,   482,    -1,   482,    25,   482,    -1,   482,
      29,   482,    -1,   482,    31,   482,    -1,   482,    28,   482,
      -1,   482,    30,   482,    -1,   482,    32,   482,    -1,   482,
      24,   482,    -1,   482,    33,   482,    -1,   482,    38,   482,
      -1,   482,    35,   482,    -1,   482,    22,   482,    -1,    34,
     482,    -1,   482,    23,   482,    -1,   482,   366,   482,    -1,
      17,    -1,    16,    -1,   354,    -1,   485,    -1,   488,    -1,
     487,    -1,   485,    15,   559,   478,    21,    -1,   485,    15,
     559,   478,    21,   492,    -1,   488,    15,   478,    21,    -1,
     488,    15,   478,    21,   492,    -1,   486,     3,   129,    -1,
     485,    -1,   488,    -1,   485,    15,   559,   478,    21,    -1,
     488,    15,   478,    21,    -1,   485,   492,    -1,    -1,   492,
      -1,    15,   493,     7,   493,    21,    -1,    -1,   482,    -1,
     495,    -1,   495,   246,   499,    -1,   496,    -1,   496,   246,
     499,    -1,   497,   491,    -1,    36,    -1,    27,    -1,   201,
      -1,    92,    -1,   149,    -1,    64,    -1,   485,   246,    64,
      -1,   496,   246,    64,    -1,    15,   483,     8,   483,    21,
      -1,   485,    -1,   496,    -1,   482,     7,   482,    -1,   482,
       7,    -1,   482,     7,   482,     7,   482,    -1,   482,     7,
       7,   482,    -1,     7,   482,     7,   482,    -1,     7,     7,
     482,    -1,     7,   482,    -1,     7,    -1,    -1,    -1,    14,
     395,   502,   556,   503,    20,    -1,   485,    -1,   488,    -1,
     489,    -1,   505,     8,   559,   489,    -1,   505,     8,   559,
     550,   485,    -1,   504,    -1,   506,     8,   559,   504,    -1,
     506,     8,   559,   550,   485,    -1,    -1,   485,    -1,   508,
       8,   485,    -1,   530,    -1,   529,    -1,   512,    -1,   520,
     512,    -1,   102,   538,   518,    -1,   103,   538,   517,    -1,
     108,   518,    -1,   510,    -1,   520,   510,    -1,   521,   530,
      -1,   521,   239,    -1,   520,   521,   239,    -1,    97,   538,
      15,   482,    21,   239,   517,    -1,    96,   538,   517,    -1,
     106,   538,   517,    -1,   513,    -1,    76,   538,    -1,   522,
     530,    -1,   522,    -1,   520,   522,    -1,   105,   538,   517,
      -1,   565,    -1,   828,    -1,   844,    -1,    89,   538,    15,
     482,    21,    -1,    89,   538,   539,   528,   540,   599,   511,
      -1,    -1,     8,   361,   254,    15,   482,    21,    -1,   254,
      15,   482,    21,    -1,   185,   538,   539,   528,   540,   533,
     526,    26,   482,     8,   482,    -1,   185,   538,   539,   528,
     540,   533,   526,    26,   482,     8,   482,     8,   482,    -1,
      62,   538,   514,   517,    -1,    84,   538,   517,    -1,   110,
     538,   517,    -1,   218,   538,   361,    62,    15,   482,    21,
      -1,   520,   218,   538,   361,    62,    15,   482,    21,    -1,
      15,   516,    21,    -1,   482,    -1,   482,     7,    -1,     7,
     482,    -1,   482,     7,   482,    -1,   515,    -1,   516,     8,
     515,    -1,    -1,   354,    -1,    -1,   354,    -1,    75,    -1,
     519,     7,    -1,   155,   538,    15,   482,    21,    -1,   122,
     538,    15,   523,   525,    21,    -1,   524,    -1,   523,     8,
     524,    -1,   526,    26,   500,    -1,    -1,     8,   482,    -1,
     354,    -1,   526,    26,   482,     8,   482,    -1,   526,    26,
     482,     8,   482,     8,   482,    -1,    -1,   149,    -1,   113,
     538,   517,    -1,    98,   538,   517,    -1,    98,   538,    15,
     482,    21,   517,    -1,   252,   538,    15,   482,    21,    -1,
     520,   252,   538,    15,   482,    21,    -1,   531,   482,    26,
     482,    -1,   188,   538,   486,    18,   482,    -1,    48,   538,
     465,   240,   354,    -1,    77,   538,    -1,   532,    -1,   541,
      -1,    46,   538,    15,   482,    21,   465,     8,   465,     8,
     465,    -1,   534,    -1,   534,    15,    21,    -1,   534,    15,
     535,    21,    -1,   214,   538,   493,    -1,   537,   538,   493,
      -1,    79,   538,   517,    -1,   115,   538,   517,    -1,    45,
     538,    15,   507,   505,    21,    -1,    81,   538,    15,   507,
     506,    21,    -1,   170,   538,    15,   508,    21,    -1,   253,
     538,    15,   482,    21,   486,    26,   482,    -1,   152,   415,
      -1,   186,   538,   465,    -1,    49,   538,   354,    -1,    49,
     538,   354,   533,    15,   464,    21,    -1,    69,   538,    15,
     464,    21,   533,   482,    -1,    -1,     8,    -1,    61,   538,
     354,   559,    -1,   559,   536,    -1,   535,     8,   559,   536,
      -1,   482,    -1,   550,   482,    -1,     5,   465,    -1,   184,
      -1,   232,    -1,    -1,    -1,    -1,   542,   547,    -1,   542,
     562,    -1,   542,     5,    -1,   542,     9,    -1,   544,   547,
      -1,   551,   547,    -1,   551,   546,    -1,   551,   547,   554,
      -1,   551,   546,     8,   554,    -1,   552,   547,    -1,   552,
     547,   556,    -1,   553,    -1,   553,     8,   556,    -1,   543,
     538,   560,    -1,    53,    -1,   215,    -1,   104,    -1,   545,
     538,   560,    -1,   139,    -1,   176,    -1,    66,    -1,   562,
      -1,     5,    -1,    15,   561,    21,    -1,    15,   548,    21,
      -1,   549,    -1,   548,     8,   559,   549,    -1,   561,    -1,
       5,    -1,     9,    -1,   550,   482,    -1,   550,     5,    -1,
     550,     9,    -1,   166,    -1,   197,   538,   560,    -1,   256,
     538,   560,    -1,   190,   538,   561,   560,    -1,   190,   538,
       5,   560,    -1,   555,    -1,   554,     8,   555,    -1,   486,
      -1,    15,   554,     8,   527,    21,    -1,   483,    -1,   558,
      -1,   557,    -1,   483,     8,   483,    -1,   483,     8,   558,
      -1,   558,     8,   483,    -1,   558,     8,   558,    -1,   557,
       8,   483,    -1,   557,     8,   558,    -1,   498,    -1,    15,
     482,    21,    -1,    15,   483,     8,   527,    21,    -1,    15,
     558,     8,   527,    21,    -1,    15,   557,     8,   527,    21,
      -1,    -1,    -1,   562,    -1,    15,   561,    21,    -1,   486,
      -1,   494,    -1,   561,   484,   561,    -1,   561,     5,   561,
      -1,   561,    37,   561,    -1,   561,     9,   561,    -1,   484,
     561,    -1,   561,    23,   561,    -1,   129,    26,   482,    -1,
      -1,   257,    -1,   566,    -1,   614,    -1,   589,    -1,   568,
      -1,   579,    -1,   574,    -1,   626,    -1,   629,    -1,   705,
      -1,   571,    -1,   580,    -1,   582,    -1,   584,    -1,   586,
      -1,   634,    -1,   640,    -1,   637,    -1,   765,    -1,   763,
      -1,   590,    -1,   615,    -1,   644,    -1,   694,    -1,   692,
      -1,   693,    -1,   695,    -1,   696,    -1,   697,    -1,   698,
      -1,   699,    -1,   707,    -1,   709,    -1,   714,    -1,   711,
      -1,   713,    -1,   717,    -1,   715,    -1,   716,    -1,   728,
      -1,   732,    -1,   733,    -1,   736,    -1,   735,    -1,   737,
      -1,   738,    -1,   739,    -1,   740,    -1,   643,    -1,   722,
      -1,   723,    -1,   724,    -1,   727,    -1,   741,    -1,   744,
      -1,   749,    -1,   754,    -1,   756,    -1,   757,    -1,   758,
      -1,   759,    -1,   761,    -1,   720,    -1,   764,    -1,    82,
     476,   567,    -1,   566,     8,   567,    -1,   354,   459,    -1,
      94,   476,   569,    -1,   570,    -1,   569,     8,   570,    -1,
     354,    -1,   138,   476,   572,    -1,   573,    -1,   572,     8,
     573,    -1,   354,    -1,   228,   476,   578,   575,    -1,    15,
     576,    21,    -1,   577,    -1,   576,     8,   577,    -1,   482,
      -1,   482,     7,   482,    -1,     7,    15,   481,    21,    -1,
     354,    -1,   259,   476,   354,   459,    -1,   303,   476,   354,
     459,    -1,   579,     8,   354,   459,    -1,   136,   476,   581,
      -1,   580,     8,   581,    -1,   354,    -1,   211,   476,   583,
      -1,   582,     8,   583,    -1,   354,    -1,   205,   476,   585,
      -1,   584,     8,   585,    -1,   354,    -1,    70,   476,   587,
      -1,   586,     8,   587,    -1,   354,    -1,   175,   354,   459,
      -1,    -1,    88,   476,   593,   596,   588,    -1,   204,   538,
     593,   597,   599,   588,    -1,   204,   538,   597,   599,   588,
       7,     7,   591,    -1,   592,    -1,   591,     8,   592,    -1,
     593,    -1,   594,    -1,   354,    -1,   354,    15,   481,    21,
      -1,   354,    -1,    -1,   597,   599,    -1,    15,   598,    21,
      -1,   599,   600,    -1,   598,     8,   599,   600,    -1,    -1,
      58,    -1,    58,    15,   559,   613,    21,    -1,   126,    15,
     601,    21,    -1,   258,    15,   601,     8,   482,    21,    -1,
     165,    15,   482,    21,    -1,     5,    -1,   137,    15,   601,
      21,    -1,    86,    15,   602,    21,    -1,   354,    -1,    15,
     603,    21,   361,   255,   605,    -1,   604,    -1,   603,     8,
     604,    -1,   482,    -1,   482,     7,   482,    -1,   606,    -1,
     606,    15,   607,    21,    -1,   354,    -1,   608,    -1,   607,
       8,   608,    -1,   482,    -1,   753,    -1,    40,   609,   610,
      -1,   354,    -1,    -1,   611,    -1,    17,   612,    -1,   610,
      17,   612,    -1,   482,    -1,   550,   482,    -1,   550,   482,
       8,   550,   482,    -1,    43,   476,   617,   619,    -1,   199,
     538,   618,   619,    -1,   199,   538,   619,     7,     7,   616,
      -1,   618,    -1,   616,     8,   618,    -1,   354,    -1,   485,
      -1,    15,   624,    21,   361,   255,   620,    -1,   623,    15,
     621,    21,    -1,   622,    -1,   621,     8,   622,    -1,   482,
      -1,     5,    -1,   500,    -1,   354,    -1,   625,    -1,   624,
       8,   625,    -1,   354,    -1,     5,    -1,     7,    -1,   627,
       7,     7,   476,   354,   459,    -1,   626,     8,   354,   459,
      -1,   628,    -1,   627,     8,   361,   628,    -1,    82,    -1,
     259,    -1,   303,    -1,    94,    -1,    87,    15,   460,    21,
      -1,   228,   575,    -1,    43,    15,   624,    21,   361,   255,
     620,    -1,    43,    -1,    88,   597,   599,   588,    -1,    88,
      -1,    67,    -1,   385,     8,   361,    93,   476,    15,   630,
      21,     7,     7,   632,    -1,    -1,   631,     7,    -1,   630,
       8,     7,    -1,   633,    -1,   632,     8,   633,    -1,   354,
      -1,   127,   476,   635,    -1,   636,    -1,   635,     8,   636,
      -1,   354,    -1,    74,   476,   638,    -1,   639,    -1,   638,
       8,   639,    -1,   354,    -1,    51,   476,   641,    -1,    51,
     476,     8,   361,    67,     7,     7,   641,    -1,   642,    -1,
     641,     8,   642,    -1,   354,   459,    -1,   168,   538,    -1,
     182,   538,    15,   645,    21,   647,   651,    -1,   646,    -1,
     645,     8,   646,    -1,   485,    -1,   599,   173,   648,    -1,
     599,    -1,   485,    15,   649,    21,    -1,   650,    -1,   649,
       8,   650,    -1,   482,    -1,     5,    -1,    -1,   652,    -1,
     653,    -1,   652,   653,    -1,   657,    -1,   677,    -1,   685,
      -1,   654,    -1,   662,    -1,   664,    -1,   663,    -1,   655,
      -1,   658,    -1,   659,    -1,     8,   361,   209,    15,   700,
       7,   701,    21,    -1,     8,   361,   209,    15,   701,    21,
      -1,     8,   361,    71,    15,   656,     7,   701,    21,    -1,
       8,   361,    71,    15,   701,    21,    -1,   354,    -1,     8,
     361,   169,    15,   661,    21,    -1,     8,   361,   282,    15,
     661,    21,    -1,     8,   361,   191,    15,   661,    21,    -1,
       8,   361,   320,    15,   660,    21,    -1,   482,    -1,   482,
       8,   482,    -1,   482,     8,   482,     8,   482,    -1,   486,
      -1,   661,     8,   486,    -1,     8,   361,   135,    15,   700,
       7,   718,    21,    -1,     8,   361,   135,    15,   718,    21,
      -1,     8,   361,   229,    15,   482,    21,    -1,     8,   361,
      41,   665,    -1,     8,   361,    41,   665,   665,    -1,    15,
     599,   666,   667,    21,    -1,   148,     7,    -1,   180,     7,
      -1,    -1,   668,    -1,   667,     8,   668,    -1,   690,    -1,
     690,    15,   669,    21,    -1,   690,    15,   669,    21,    15,
     671,    21,    -1,   670,    -1,   669,     8,   670,    -1,   482,
       7,   482,    -1,   672,    -1,   671,     8,   672,    -1,   673,
       7,   674,     7,   675,    -1,   673,     7,   674,    -1,   673,
       7,   675,    -1,   673,    -1,   674,     7,   675,    -1,   674,
      -1,   675,    -1,   361,   217,   676,    -1,   361,   157,   676,
      -1,   361,   128,   676,    -1,    15,   480,    21,    -1,     8,
     361,   208,    15,   678,   682,   679,     8,   681,    21,    -1,
       8,   361,   208,    15,   678,   682,   679,    21,    -1,     8,
     361,   208,    15,   678,   680,   679,     7,   681,    21,    -1,
      -1,    -1,   354,    -1,   361,   682,    -1,   681,     8,   361,
     682,    -1,   683,    15,   486,    21,    -1,   684,    15,   661,
       8,   482,    21,    -1,   234,    -1,   192,    -1,   162,    -1,
     159,    -1,    35,    -1,    22,    -1,    24,    -1,    33,    -1,
     247,    -1,   158,    -1,   161,    -1,     8,   361,   223,    15,
     687,    21,    -1,     8,   361,   224,   686,    -1,     8,   361,
     226,   686,    -1,     8,   361,   221,    -1,     8,   361,   221,
      15,   690,    15,   576,    21,    21,    -1,   354,    -1,   688,
      -1,   687,     8,   688,    -1,   690,    -1,   690,    15,   689,
      78,    21,    -1,   690,    15,   689,   576,    21,    -1,   690,
      15,   689,   576,    21,    15,   361,    78,    21,    -1,    -1,
     485,    -1,   690,    -1,   691,     8,   690,    -1,   225,   538,
     686,    -1,   224,   538,   686,    -1,   227,   538,   686,    -1,
     226,   538,   686,    -1,   222,   538,   686,    15,   687,    21,
      -1,   206,   538,   680,    -1,   207,   538,   680,    -1,    72,
     538,   656,    -1,    73,   538,   656,    -1,   210,   538,    15,
     700,     7,   701,    21,    -1,   210,   538,    15,   701,    21,
      -1,   354,    -1,   702,    -1,   701,     8,   702,    -1,   690,
      15,   703,    21,    -1,   690,    -1,   704,    -1,   703,     8,
     704,    -1,   482,    -1,     7,    -1,   237,   476,   706,    -1,
     705,     8,   706,    -1,   354,   459,    -1,   238,   538,   708,
      -1,   238,   538,   708,   677,    -1,   238,   538,   708,   655,
      -1,   238,   538,   708,   677,   655,    -1,   238,   538,   708,
     655,   677,    -1,   354,    -1,   111,   538,    -1,   708,    15,
     482,    21,    -1,   708,    15,   500,    21,    -1,   174,   538,
     487,   712,    -1,    -1,   657,    -1,   109,   538,    -1,   160,
     538,   710,   361,   175,   595,   459,    -1,   160,   538,   710,
     361,   321,   486,    -1,   189,   538,   700,    -1,   212,   538,
     700,    -1,   135,   538,    15,   700,     7,   718,    21,    -1,
     135,   538,    15,   718,    21,    -1,   719,    -1,   718,     8,
     719,    -1,   690,    -1,   690,    15,   481,    21,    -1,   134,
     538,    -1,   134,   538,   657,    -1,   134,   538,   721,    -1,
     134,   538,   657,   721,    -1,     8,   361,   208,    15,   661,
      21,    -1,    50,   538,   726,    -1,    99,   538,    -1,    52,
     538,   726,    -1,   354,    -1,   725,    -1,   725,    15,   481,
      21,    -1,   120,   538,   486,    26,   486,    -1,    83,   538,
     731,    -1,    83,   538,   731,    15,   729,    21,    -1,   559,
     730,    -1,   729,     8,   559,   730,    -1,   550,   482,    -1,
     149,    -1,   100,   538,   731,    -1,   146,   538,   734,    -1,
      -1,   482,    -1,   330,   538,   481,    -1,   101,   538,    -1,
     241,   538,    -1,   242,   538,    -1,    56,   538,    -1,    65,
     538,   559,    15,   535,    21,   395,   477,   661,    -1,   322,
     538,    15,   742,    21,    -1,   743,    -1,   742,     8,   743,
      -1,   361,   315,    -1,   361,   318,    -1,   361,   182,    -1,
     220,   538,    15,   745,    26,   612,    21,   599,   748,    -1,
     485,    15,   746,    21,    -1,   747,    -1,   746,     8,   747,
      -1,   602,    -1,   753,    -1,   132,   691,    -1,    -1,   153,
     538,    15,   485,    18,   750,    21,    -1,   485,    -1,   485,
      15,   751,    21,    -1,   752,    -1,   751,     8,   752,    -1,
     753,    -1,     7,    -1,     5,    -1,   323,   538,   482,     8,
     361,   328,    15,   661,    21,     8,   361,   327,    15,   481,
      21,   755,    -1,    -1,     8,   361,   182,    -1,     8,   361,
     318,    -1,   324,   538,   482,    -1,   325,   538,   482,    -1,
     325,   538,   482,     8,   361,   315,    -1,   326,   538,   482,
       8,   361,   329,    15,   485,    21,    -1,   331,   538,    15,
     760,    21,    -1,   489,    -1,   760,     8,   489,    -1,   332,
     538,    15,   762,    21,    -1,   485,    -1,   762,     8,   485,
      -1,   814,    -1,   767,    -1,   766,    -1,   784,    -1,   787,
      -1,   788,    -1,   789,    -1,   790,    -1,   796,    -1,   799,
      -1,   804,    -1,   805,    -1,   806,    -1,   809,    -1,   810,
      -1,   811,    -1,   812,    -1,   813,    -1,   815,    -1,   816,
      -1,   817,    -1,   818,    -1,   819,    -1,   820,    -1,   821,
      -1,   822,    -1,   823,    -1,   268,   538,    -1,   275,   538,
      -1,   291,   538,   599,   768,    -1,   291,   538,   599,    -1,
     533,   599,   769,   599,    -1,   768,   533,   599,   769,   599,
      -1,   771,    -1,   780,    -1,   775,    -1,   776,    -1,   772,
      -1,   773,    -1,   774,    -1,   778,    -1,   779,    -1,   826,
      15,   827,   825,    21,    -1,   191,   770,    -1,   282,   770,
      -1,   285,   770,    -1,   265,   770,    -1,   299,   770,    -1,
      84,    15,   361,   777,    21,    -1,   191,    -1,   299,    -1,
     288,    -1,   304,    15,   482,    21,    -1,   289,    15,   482,
      21,    -1,   208,    15,   781,    21,    -1,   599,   783,     7,
     782,    -1,   661,    -1,    17,    -1,    16,    -1,     5,    -1,
      37,    -1,   162,    -1,   159,    -1,    35,    -1,    22,    -1,
      24,    -1,    33,    -1,   305,    -1,   306,    -1,   307,    -1,
     247,    -1,   297,   538,   599,   785,    -1,   297,   538,   599,
      -1,   533,   599,   786,   599,    -1,   785,   533,   599,   786,
     599,    -1,   771,    -1,   780,    -1,   772,    -1,   773,    -1,
     279,   538,   599,   803,    -1,   279,   538,   599,    -1,   296,
     538,    -1,   269,   538,   599,   791,    -1,   269,   538,   599,
      -1,   272,   538,   599,   803,    -1,   272,   538,   599,    -1,
     533,   599,   792,   599,    -1,   791,   533,   599,   792,   599,
      -1,   771,    -1,   780,    -1,   772,    -1,   773,    -1,   794,
      -1,   793,    -1,   290,    -1,   298,    15,   361,   795,     8,
     482,    21,    -1,   298,    15,   361,   795,    21,    -1,   230,
      -1,    94,    -1,   284,    -1,   295,    -1,   300,   538,   599,
     797,    -1,   300,   538,   599,    -1,   533,   599,   798,   599,
      -1,   797,   533,   599,   798,   599,    -1,   771,    -1,   772,
      -1,   280,   538,   599,   800,    -1,   280,   538,   599,    -1,
     533,   599,   801,   599,    -1,   800,   533,   599,   801,   599,
      -1,   803,    -1,   802,    -1,   266,   770,    -1,   287,    -1,
     302,   538,    -1,   281,   538,   599,   803,    -1,   281,   538,
     599,    -1,   292,   538,   599,   807,    -1,   292,   538,   599,
      -1,   533,   599,   808,   599,    -1,   807,   533,   599,   808,
     599,    -1,   771,    -1,   780,    -1,   775,    -1,   776,    -1,
     772,    -1,   773,    -1,   774,    -1,   778,    -1,   779,    -1,
     794,    -1,   793,    -1,   276,   538,    -1,   293,   538,   599,
     768,    -1,   293,   538,   599,    -1,   277,   538,    -1,   294,
     538,   599,   768,    -1,   294,   538,   599,    -1,   278,   538,
      -1,   301,   476,   770,    -1,   286,   538,    -1,   273,   538,
      -1,   290,   538,    -1,   274,   538,    -1,   264,   538,    -1,
     263,   538,    -1,   283,   538,   770,    -1,   283,   538,    -1,
     267,   538,    15,   485,    21,    -1,   267,   538,    -1,   271,
     538,    15,   485,    21,    -1,   271,   538,    -1,    37,   354,
     826,    37,   827,    -1,   824,    -1,   485,    -1,   825,     8,
     824,    -1,   825,     8,   485,    -1,    -1,    -1,   829,    -1,
     842,    -1,   830,    -1,   843,    -1,   831,    -1,   832,    -1,
     308,   538,   833,    -1,   310,   538,    -1,   312,   538,    15,
     839,    21,    -1,   312,   538,    15,    21,    -1,   312,   538,
      -1,   313,   538,    15,   839,    21,    -1,   313,   538,    15,
      21,    -1,   313,   538,    -1,   361,   362,    -1,   834,    -1,
     835,    -1,   834,     8,   835,    -1,   361,   836,    -1,   361,
     838,    -1,   361,   837,    -1,   147,    15,   839,    21,    -1,
     148,    15,   839,    21,    -1,   180,    15,   839,    21,    -1,
     318,    15,   839,    21,    -1,   319,    15,   839,    21,    -1,
     314,    15,   840,    21,    -1,   315,    -1,   661,    -1,   841,
      -1,   840,     8,   841,    -1,   361,   316,    -1,   361,   317,
      -1,   309,    -1,   311,    -1,   845,    -1,   846,    -1,   847,
      -1,   848,    -1,   849,    -1,   333,    15,   850,    21,    -1,
     334,    15,   854,    21,    -1,   335,    15,   859,    21,    -1,
     337,   861,    -1,   338,    -1,   851,    -1,   850,     8,   851,
      -1,   852,    -1,   853,    -1,   361,   208,    15,   681,    21,
      -1,   361,   191,    15,   661,    21,    -1,   855,    -1,   854,
       8,   855,    -1,   856,    -1,   857,    -1,   858,    -1,   361,
     228,    15,   687,    21,    -1,   361,    41,    15,   687,    21,
      -1,   361,   209,    15,   701,    21,    -1,   860,    -1,   859,
       8,   860,    -1,   361,   336,    -1,   361,   340,    15,   645,
      21,    -1,   361,   339,    -1,   361,   339,    15,   645,    21,
      -1,   354,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   770,   770,   771,   775,   777,   791,   822,   831,   837,
     857,   866,   882,   894,   904,   911,   917,   922,   927,   951,
     978,   992,   994,   996,  1000,  1017,  1031,  1055,  1071,  1085,
    1103,  1105,  1112,  1116,  1117,  1124,  1125,  1133,  1134,  1136,
    1140,  1141,  1145,  1149,  1155,  1165,  1169,  1174,  1181,  1182,
    1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,
    1193,  1194,  1199,  1204,  1211,  1213,  1214,  1215,  1216,  1217,
    1218,  1219,  1220,  1221,  1222,  1223,  1224,  1227,  1231,  1239,
    1247,  1256,  1264,  1268,  1270,  1274,  1276,  1278,  1280,  1282,
    1284,  1286,  1288,  1290,  1292,  1294,  1296,  1298,  1300,  1302,
    1304,  1306,  1308,  1313,  1322,  1332,  1340,  1350,  1371,  1391,
    1392,  1394,  1398,  1400,  1404,  1408,  1410,  1414,  1420,  1424,
    1426,  1430,  1434,  1438,  1442,  1446,  1452,  1456,  1460,  1466,
    1471,  1478,  1489,  1502,  1513,  1526,  1536,  1549,  1554,  1561,
    1564,  1569,  1574,  1581,  1584,  1594,  1608,  1611,  1630,  1657,
    1659,  1671,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1690,
    1691,  1695,  1697,  1704,  1709,  1710,  1712,  1714,  1727,  1733,
    1739,  1748,  1757,  1770,  1771,  1774,  1778,  1793,  1808,  1826,
    1847,  1867,  1889,  1906,  1924,  1931,  1938,  1945,  1958,  1965,
    1972,  1983,  1987,  1989,  1994,  2012,  2023,  2035,  2047,  2061,
    2067,  2074,  2080,  2086,  2094,  2101,  2117,  2120,  2129,  2131,
    2135,  2139,  2159,  2163,  2165,  2169,  2170,  2173,  2175,  2177,
    2179,  2181,  2184,  2187,  2191,  2197,  2201,  2205,  2207,  2212,
    2213,  2217,  2221,  2223,  2227,  2229,  2231,  2236,  2240,  2242,
    2244,  2247,  2249,  2250,  2251,  2252,  2253,  2254,  2255,  2256,
    2259,  2260,  2266,  2269,  2270,  2272,  2276,  2277,  2280,  2281,
    2283,  2287,  2288,  2289,  2290,  2292,  2295,  2296,  2305,  2307,
    2314,  2321,  2328,  2337,  2339,  2341,  2345,  2347,  2351,  2360,
    2367,  2374,  2376,  2380,  2384,  2390,  2392,  2397,  2401,  2405,
    2412,  2419,  2429,  2431,  2435,  2447,  2450,  2459,  2472,  2478,
    2484,  2490,  2498,  2508,  2510,  2514,  2535,  2560,  2562,  2566,
    2598,  2599,  2603,  2603,  2608,  2612,  2620,  2629,  2638,  2648,
    2654,  2657,  2659,  2663,  2671,  2686,  2693,  2695,  2699,  2715,
    2715,  2719,  2721,  2733,  2735,  2739,  2745,  2757,  2769,  2786,
    2815,  2816,  2824,  2825,  2829,  2831,  2833,  2844,  2848,  2854,
    2856,  2860,  2862,  2864,  2868,  2870,  2874,  2876,  2878,  2880,
    2882,  2884,  2886,  2888,  2890,  2892,  2894,  2896,  2898,  2900,
    2902,  2904,  2906,  2908,  2910,  2912,  2914,  2916,  2918,  2922,
    2923,  2934,  3008,  3020,  3022,  3026,  3157,  3207,  3251,  3293,
    3351,  3353,  3355,  3394,  3437,  3448,  3449,  3453,  3458,  3459,
    3463,  3465,  3471,  3473,  3479,  3489,  3495,  3502,  3508,  3516,
    3524,  3540,  3550,  3563,  3570,  3572,  3595,  3597,  3599,  3601,
    3603,  3605,  3607,  3609,  3613,  3613,  3613,  3627,  3629,  3652,
    3654,  3656,  3672,  3674,  3676,  3690,  3693,  3695,  3703,  3705,
    3707,  3709,  3763,  3783,  3798,  3807,  3810,  3860,  3866,  3871,
    3889,  3891,  3893,  3895,  3897,  3900,  3906,  3908,  3910,  3913,
    3915,  3917,  3944,  3953,  3962,  3963,  3965,  3970,  3977,  3985,
    3987,  3991,  3994,  3996,  4000,  4006,  4008,  4010,  4012,  4016,
    4018,  4027,  4028,  4035,  4036,  4040,  4044,  4065,  4068,  4072,
    4074,  4081,  4086,  4087,  4098,  4115,  4138,  4163,  4164,  4171,
    4173,  4175,  4177,  4179,  4183,  4260,  4272,  4279,  4281,  4282,
    4284,  4293,  4300,  4307,  4315,  4320,  4325,  4328,  4331,  4334,
    4337,  4340,  4344,  4362,  4367,  4386,  4405,  4409,  4410,  4413,
    4417,  4422,  4429,  4431,  4433,  4437,  4438,  4449,  4464,  4468,
    4475,  4478,  4488,  4501,  4514,  4518,  4521,  4524,  4528,  4537,
    4540,  4544,  4546,  4552,  4556,  4558,  4560,  4567,  4571,  4573,
    4575,  4579,  4598,  4614,  4623,  4632,  4634,  4638,  4664,  4679,
    4694,  4711,  4719,  4728,  4736,  4741,  4746,  4768,  4784,  4786,
    4790,  4792,  4799,  4801,  4803,  4807,  4809,  4811,  4813,  4815,
    4817,  4821,  4824,  4827,  4833,  4839,  4848,  4852,  4859,  4861,
    4865,  4867,  4869,  4874,  4879,  4884,  4889,  4898,  4903,  4909,
    4910,  4925,  4926,  4927,  4928,  4929,  4930,  4931,  4932,  4933,
    4934,  4935,  4936,  4937,  4938,  4939,  4940,  4941,  4942,  4943,
    4946,  4947,  4948,  4949,  4950,  4951,  4952,  4953,  4954,  4955,
    4956,  4957,  4958,  4959,  4960,  4961,  4962,  4963,  4964,  4965,
    4966,  4967,  4968,  4969,  4970,  4971,  4972,  4973,  4974,  4975,
    4976,  4977,  4978,  4979,  4980,  4981,  4982,  4983,  4984,  4985,
    4986,  4987,  4988,  4989,  4993,  4995,  5006,  5027,  5031,  5033,
    5037,  5050,  5054,  5056,  5060,  5071,  5082,  5086,  5088,  5092,
    5094,  5096,  5111,  5123,  5143,  5163,  5185,  5191,  5200,  5208,
    5214,  5222,  5229,  5235,  5244,  5248,  5254,  5262,  5276,  5290,
    5295,  5311,  5326,  5354,  5356,  5360,  5362,  5366,  5395,  5418,
    5439,  5440,  5444,  5465,  5467,  5471,  5479,  5483,  5488,  5490,
    5492,  5494,  5500,  5502,  5506,  5516,  5520,  5522,  5527,  5529,
    5533,  5537,  5543,  5553,  5555,  5559,  5561,  5563,  5570,  5588,
    5589,  5593,  5595,  5599,  5606,  5616,  5645,  5660,  5667,  5685,
    5687,  5691,  5705,  5731,  5744,  5760,  5762,  5765,  5767,  5773,
    5777,  5805,  5807,  5811,  5819,  5825,  5828,  5886,  5950,  5952,
    5955,  5959,  5963,  5967,  5984,  5996,  6000,  6004,  6014,  6019,
    6024,  6031,  6040,  6040,  6051,  6062,  6064,  6068,  6079,  6083,
    6085,  6089,  6100,  6104,  6106,  6110,  6122,  6124,  6131,  6133,
    6137,  6153,  6161,  6172,  6174,  6178,  6181,  6184,  6189,  6199,
    6201,  6205,  6207,  6216,  6217,  6221,  6223,  6228,  6229,  6230,
    6231,  6232,  6233,  6234,  6235,  6236,  6237,  6240,  6245,  6249,
    6253,  6257,  6270,  6274,  6278,  6282,  6285,  6287,  6289,  6293,
    6295,  6299,  6304,  6308,  6312,  6314,  6318,  6326,  6332,  6339,
    6342,  6344,  6348,  6350,  6354,  6366,  6368,  6372,  6376,  6378,
    6382,  6384,  6386,  6388,  6390,  6392,  6394,  6398,  6402,  6406,
    6410,  6414,  6421,  6427,  6432,  6435,  6438,  6451,  6453,  6457,
    6459,  6464,  6470,  6476,  6482,  6488,  6494,  6500,  6506,  6512,
    6521,  6527,  6544,  6546,  6554,  6562,  6564,  6568,  6572,  6574,
    6578,  6580,  6588,  6592,  6604,  6607,  6625,  6627,  6631,  6633,
    6637,  6639,  6643,  6647,  6651,  6660,  6664,  6668,  6673,  6677,
    6689,  6691,  6695,  6700,  6704,  6706,  6710,  6712,  6716,  6721,
    6728,  6751,  6753,  6755,  6757,  6759,  6763,  6774,  6778,  6793,
    6800,  6807,  6808,  6812,  6816,  6824,  6828,  6832,  6840,  6845,
    6859,  6861,  6865,  6867,  6876,  6878,  6880,  6882,  6918,  6922,
    6926,  6930,  6934,  6946,  6948,  6952,  6955,  6957,  6961,  6966,
    6973,  6976,  6984,  6988,  6993,  6995,  7002,  7007,  7011,  7015,
    7019,  7023,  7027,  7030,  7032,  7036,  7038,  7040,  7044,  7048,
    7060,  7062,  7066,  7068,  7072,  7075,  7078,  7082,  7088,  7100,
    7102,  7106,  7108,  7112,  7120,  7132,  7133,  7135,  7139,  7143,
    7145,  7153,  7157,  7160,  7162,  7166,  7170,  7172,  7175,  7177,
    7178,  7179,  7180,  7181,  7182,  7183,  7184,  7185,  7186,  7187,
    7188,  7189,  7190,  7191,  7192,  7193,  7194,  7195,  7196,  7197,
    7198,  7199,  7200,  7201,  7202,  7205,  7211,  7217,  7223,  7229,
    7233,  7239,  7240,  7241,  7242,  7243,  7244,  7245,  7246,  7247,
    7250,  7255,  7260,  7266,  7272,  7278,  7283,  7289,  7295,  7301,
    7308,  7314,  7320,  7327,  7331,  7333,  7339,  7346,  7352,  7358,
    7364,  7370,  7376,  7382,  7388,  7394,  7400,  7406,  7412,  7422,
    7427,  7433,  7437,  7443,  7444,  7445,  7446,  7449,  7457,  7463,
    7469,  7474,  7480,  7487,  7493,  7497,  7503,  7504,  7505,  7506,
    7507,  7508,  7511,  7520,  7524,  7530,  7537,  7544,  7551,  7560,
    7566,  7572,  7576,  7582,  7583,  7586,  7592,  7598,  7602,  7609,
    7610,  7613,  7619,  7625,  7630,  7638,  7644,  7649,  7656,  7660,
    7666,  7667,  7668,  7669,  7670,  7671,  7672,  7673,  7674,  7675,
    7676,  7680,  7685,  7690,  7697,  7702,  7708,  7714,  7719,  7724,
    7729,  7733,  7738,  7743,  7747,  7752,  7756,  7762,  7767,  7773,
    7778,  7784,  7794,  7798,  7802,  7806,  7812,  7815,  7819,  7820,
    7821,  7822,  7823,  7824,  7827,  7831,  7835,  7837,  7839,  7843,
    7845,  7847,  7851,  7853,  7857,  7859,  7863,  7866,  7869,  7874,
    7876,  7878,  7880,  7882,  7886,  7890,  7895,  7899,  7901,  7905,
    7907,  7911,  7915,  7919,  7920,  7921,  7922,  7923,  7926,  7930,
    7934,  7938,  7942,  7946,  7948,  7952,  7953,  7956,  7960,  7964,
    7966,  7970,  7971,  7972,  7976,  7980,  7984,  7988,  7990,  7994,
    7996,  7998,  8000,  8003
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
  "STATUS", "EXITINTERVAL", "TEMPLATE_CREATE", "TEMPLATE_DELETE",
  "SPF_ANALYSIS", "SPF_PARALLEL", "SPF_TRANSFORM", "SPF_NOINLINE",
  "SPF_PARALLEL_REG", "SPF_END_PARALLEL_REG", "SPF_PRIVATES_EXPANSION",
  "SPF_FISSION", "BINARY_OP", "UNARY_OP", "$accept", "program", "stat",
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
  "dvm_template_create", "template_list", "dvm_template_delete",
  "template_ident_list", "omp_specification_directive",
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
       0,   339,   340,     1,     2,     3,     4,     5,     6,     7,
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
     338,   341,   342
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   343,   344,   344,   345,   345,   345,   345,   345,   345,
     345,   346,   347,   347,   347,   347,   347,   347,   347,   347,
     348,   349,   349,   349,   350,   351,   352,   352,   352,   352,
     353,   353,   354,   355,   355,   356,   356,   357,   357,   357,
     358,   358,   359,   359,   360,   361,   362,   363,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   365,   365,   365,
     365,   365,   366,   367,   367,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   369,   369,   370,   370,   371,   371,   372,
     372,   372,   373,   373,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   374,   374,   375,   375,   375,   376,
     376,   377,   377,   378,   378,   379,   379,   380,   380,   381,
     382,   383,   383,   384,   385,   385,   386,   387,   387,   388,
     388,   389,   390,   390,   390,   390,   390,   390,   390,   391,
     391,   392,   392,   392,   393,   393,   393,   393,   394,   394,
     394,   394,   395,   396,   396,   396,   397,   397,   398,   398,
     399,   399,   400,   400,   401,   401,   401,   401,   402,   402,
     402,   403,   404,   404,   405,   406,   406,   407,   407,   408,
     408,   409,   410,   410,   411,   411,   411,   412,   413,   413,
     414,   415,   416,   417,   417,   418,   418,   419,   419,   419,
     419,   419,   420,   421,   422,   423,   424,   425,   425,   426,
     426,   427,   428,   428,   429,   429,   429,   429,   430,   430,
     430,   431,   431,   431,   431,   431,   431,   431,   431,   431,
     431,   431,   432,   433,   433,   433,   434,   434,   435,   435,
     435,   436,   436,   436,   436,   437,   438,   438,   439,   439,
     439,   439,   439,   440,   440,   440,   441,   441,   442,   442,
     442,   443,   443,   444,   444,   445,   445,   446,   447,   448,
     448,   448,   449,   449,   450,   451,   452,   452,   453,   453,
     453,   453,   454,   455,   455,   456,   456,   457,   457,   458,
     459,   459,   461,   460,   460,   462,   462,   462,   462,   463,
     463,   464,   464,   465,   466,   466,   467,   467,   468,   470,
     469,   471,   471,   472,   472,   473,   473,   474,   475,   476,
     477,   477,   478,   478,   479,   479,   479,   480,   480,   481,
     481,   482,   482,   482,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   484,
     484,   485,   486,   486,   486,   487,   487,   487,   487,   488,
     489,   489,   489,   489,   490,   491,   491,   492,   493,   493,
     494,   494,   494,   494,   494,   495,   495,   495,   495,   496,
     497,   497,   497,   498,   499,   499,   500,   500,   500,   500,
     500,   500,   500,   500,   502,   503,   501,   504,   504,   505,
     505,   505,   506,   506,   506,   507,   508,   508,   509,   509,
     509,   509,   509,   509,   509,   509,   509,   509,   509,   509,
     509,   509,   509,   509,   509,   509,   509,   509,   509,   509,
     509,   509,   510,   510,   511,   511,   511,   512,   512,   513,
     513,   513,   513,   513,   514,   515,   515,   515,   515,   516,
     516,   517,   517,   518,   518,   519,   520,   521,   522,   523,
     523,   524,   525,   525,   526,   527,   527,   528,   528,   529,
     529,   529,   529,   529,   530,   530,   530,   530,   530,   530,
     530,   530,   530,   530,   530,   530,   530,   530,   530,   530,
     530,   530,   531,   532,   532,   532,   532,   533,   533,   534,
     535,   535,   536,   536,   536,   537,   537,   538,   539,   540,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   542,   543,   543,   543,   544,   545,   545,
     545,   546,   546,   547,   547,   548,   548,   549,   549,   549,
     549,   549,   549,   550,   551,   552,   553,   553,   554,   554,
     555,   555,   556,   556,   556,   557,   557,   557,   557,   557,
     557,   558,   558,   558,   558,   558,   559,   560,   561,   561,
     562,   562,   562,   562,   562,   562,   562,   562,   562,   563,
     563,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     564,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     565,   565,   565,   565,   565,   565,   565,   565,   565,   565,
     565,   565,   565,   565,   565,   565,   565,   565,   565,   565,
     565,   565,   565,   565,   565,   565,   565,   565,   565,   565,
     565,   565,   565,   565,   565,   565,   565,   565,   565,   565,
     565,   565,   565,   565,   566,   566,   567,   568,   569,   569,
     570,   571,   572,   572,   573,   574,   575,   576,   576,   577,
     577,   577,   578,   579,   579,   579,   580,   580,   581,   582,
     582,   583,   584,   584,   585,   586,   586,   587,   588,   588,
     589,   590,   590,   591,   591,   592,   592,   593,   594,   595,
     596,   596,   597,   598,   598,   599,   600,   600,   600,   600,
     600,   600,   600,   600,   601,   602,   603,   603,   604,   604,
     605,   605,   606,   607,   607,   608,   608,   608,   609,   610,
     610,   611,   611,   612,   613,   613,   614,   615,   615,   616,
     616,   617,   618,   619,   620,   621,   621,   622,   622,   622,
     623,   624,   624,   625,   625,   625,   626,   626,   627,   627,
     628,   628,   628,   628,   628,   628,   628,   628,   628,   628,
     628,   629,   631,   630,   630,   632,   632,   633,   634,   635,
     635,   636,   637,   638,   638,   639,   640,   640,   641,   641,
     642,   643,   644,   645,   645,   646,   647,   647,   648,   649,
     649,   650,   650,   651,   651,   652,   652,   653,   653,   653,
     653,   653,   653,   653,   653,   653,   653,   654,   654,   655,
     655,   656,   657,   657,   658,   659,   660,   660,   660,   661,
     661,   662,   662,   663,   664,   664,   665,   666,   666,   666,
     667,   667,   668,   668,   668,   669,   669,   670,   671,   671,
     672,   672,   672,   672,   672,   672,   672,   673,   674,   675,
     676,   677,   677,   677,   678,   679,   680,   681,   681,   682,
     682,   683,   683,   683,   683,   683,   683,   683,   683,   683,
     684,   684,   685,   685,   685,   685,   685,   686,   687,   687,
     688,   688,   688,   688,   689,   690,   691,   691,   692,   692,
     693,   693,   694,   695,   696,   697,   698,   699,   699,   700,
     701,   701,   702,   702,   703,   703,   704,   704,   705,   705,
     706,   707,   707,   707,   707,   707,   708,   709,   710,   710,
     711,   712,   712,   713,   714,   714,   715,   716,   717,   717,
     718,   718,   719,   719,   720,   720,   720,   720,   721,   722,
     723,   724,   725,   726,   726,   727,   728,   728,   729,   729,
     730,   731,   732,   733,   734,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   742,   743,   743,   743,   744,   745,
     746,   746,   747,   747,   748,   748,   749,   750,   750,   751,
     751,   752,   752,   753,   754,   755,   755,   755,   756,   757,
     757,   758,   759,   760,   760,   761,   762,   762,   763,   764,
     764,   764,   764,   764,   764,   764,   764,   764,   764,   764,
     764,   764,   764,   764,   764,   764,   764,   764,   764,   764,
     764,   764,   764,   764,   764,   765,   766,   767,   767,   768,
     768,   769,   769,   769,   769,   769,   769,   769,   769,   769,
     770,   771,   772,   773,   774,   775,   776,   777,   777,   777,
     778,   779,   780,   781,   782,   783,   783,   783,   783,   783,
     783,   783,   783,   783,   783,   783,   783,   783,   783,   784,
     784,   785,   785,   786,   786,   786,   786,   787,   787,   788,
     789,   789,   790,   790,   791,   791,   792,   792,   792,   792,
     792,   792,   793,   794,   794,   795,   795,   795,   795,   796,
     796,   797,   797,   798,   798,   799,   799,   800,   800,   801,
     801,   802,   803,   804,   805,   805,   806,   806,   807,   807,
     808,   808,   808,   808,   808,   808,   808,   808,   808,   808,
     808,   809,   810,   810,   811,   812,   812,   813,   814,   815,
     816,   817,   818,   819,   820,   821,   821,   822,   822,   823,
     823,   824,   825,   825,   825,   825,   826,   827,   828,   828,
     828,   828,   828,   828,   829,   830,   831,   831,   831,   832,
     832,   832,   833,   833,   834,   834,   835,   835,   835,   836,
     836,   836,   836,   836,   837,   838,   839,   840,   840,   841,
     841,   842,   843,   844,   844,   844,   844,   844,   845,   846,
     847,   848,   849,   850,   850,   851,   851,   852,   853,   854,
     854,   855,   855,   855,   856,   857,   858,   859,   859,   860,
     860,   860,   860,   861
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
       1,     1,     1,     1,     3,     3,     2,     3,     1,     3,
       1,     3,     1,     3,     1,     4,     3,     1,     3,     1,
       3,     4,     1,     4,     4,     4,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     0,
       5,     6,     8,     1,     3,     1,     1,     1,     4,     1,
       0,     2,     3,     2,     4,     0,     1,     5,     4,     6,
       4,     1,     4,     4,     1,     6,     1,     3,     1,     3,
       1,     4,     1,     1,     3,     1,     1,     3,     1,     0,
       1,     2,     3,     1,     2,     5,     4,     4,     6,     1,
       3,     1,     1,     6,     4,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     6,     4,     1,     4,
       1,     1,     1,     1,     4,     2,     7,     1,     4,     1,
       1,    11,     0,     2,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     8,     1,     3,
       2,     2,     7,     1,     3,     1,     3,     1,     4,     1,
       3,     1,     1,     0,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     8,     6,     8,
       6,     1,     6,     6,     6,     6,     1,     3,     5,     1,
       3,     8,     6,     6,     4,     5,     5,     2,     2,     0,
       1,     3,     1,     4,     7,     1,     3,     3,     1,     3,
       5,     3,     3,     1,     3,     1,     1,     3,     3,     3,
       3,    10,     8,    10,     0,     0,     1,     2,     4,     4,
       6,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     6,     4,     4,     3,     9,     1,     1,     3,
       1,     5,     5,     9,     0,     1,     1,     3,     3,     3,
       3,     3,     6,     3,     3,     3,     3,     7,     5,     1,
       1,     3,     4,     1,     1,     3,     1,     1,     3,     3,
       2,     3,     4,     4,     5,     5,     1,     2,     4,     4,
       4,     0,     1,     2,     7,     6,     3,     3,     7,     5,
       1,     3,     1,     4,     2,     3,     3,     4,     6,     3,
       2,     3,     1,     1,     4,     5,     3,     6,     2,     4,
       2,     1,     3,     3,     0,     1,     3,     2,     2,     2,
       2,     9,     5,     1,     3,     2,     2,     2,     9,     4,
       1,     3,     1,     1,     2,     0,     7,     1,     4,     1,
       3,     1,     1,     1,    16,     0,     3,     3,     3,     3,
       6,     9,     5,     1,     3,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     4,     3,     4,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     2,     2,     2,     2,     2,     5,     1,     1,     1,
       4,     4,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     4,     5,     1,     1,     1,     1,     4,     3,     2,
       4,     3,     4,     3,     4,     5,     1,     1,     1,     1,
       1,     1,     1,     7,     5,     1,     1,     1,     1,     4,
       3,     4,     5,     1,     1,     4,     3,     4,     5,     1,
       1,     2,     1,     2,     4,     3,     4,     3,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     4,     3,     2,     4,     3,     2,     3,     2,
       2,     2,     2,     2,     2,     3,     2,     5,     2,     5,
       2,     5,     1,     1,     3,     3,     0,     0,     1,     1,
       1,     1,     1,     1,     3,     2,     5,     4,     2,     5,
       4,     2,     2,     1,     1,     3,     2,     2,     2,     4,
       4,     4,     4,     4,     4,     1,     1,     1,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     2,     1,     1,     3,     1,     1,     5,     5,     1,
       3,     1,     1,     1,     5,     5,     5,     1,     3,     2,
       5,     2,     5,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,    10,    11,     9,     0,     0,     3,   150,
     149,   787,   339,   537,   537,   537,   537,   537,   339,   537,
     554,   537,    20,   537,   537,   158,   537,   560,   339,   154,
     537,   339,   537,   537,   339,   485,   537,   537,   537,   338,
     537,   780,   537,   537,   340,   789,   537,   155,   156,   783,
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
       0,   339,     8,   339,   537,   537,   537,   781,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   339,   537,   782,   537,  1221,   537,
    1222,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,     0,     0,     0,     0,  1232,   609,     0,    37,   609,
      73,    48,    49,    50,    65,    66,    76,    68,    69,    67,
     109,    58,     0,   146,   151,    52,    70,    71,    72,    51,
      59,    54,    55,    56,    60,   207,    75,    74,    57,   609,
     445,   440,   453,     0,     0,     0,   456,   439,   438,     0,
     508,   511,   537,   509,     0,   537,     0,   537,     0,     0,
     551,    53,   459,   611,   614,   620,   616,   615,   621,   622,
     623,   624,   613,   630,   612,   631,   617,     0,   778,   618,
     625,   627,   626,   658,   632,   634,   635,   633,   636,   637,
     638,   639,   640,   619,   641,   642,   644,   645,   643,   647,
     648,   646,   672,   659,   660,   661,   662,   649,   650,   651,
     653,   652,   654,   655,   656,   657,   663,   664,   665,   666,
     667,   668,   669,   670,   671,   629,   673,   628,  1030,  1029,
    1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,  1040,
    1041,  1042,  1043,  1044,  1045,  1028,  1046,  1047,  1048,  1049,
    1050,  1051,  1052,  1053,  1054,   460,  1188,  1190,  1192,  1193,
    1189,  1191,   461,  1223,  1224,  1225,  1226,  1227,     0,     0,
     340,     0,     0,     0,     0,     0,     0,     0,   990,    35,
       0,     0,   596,     0,     0,     0,     0,     0,     0,   454,
     507,   481,   210,     0,     0,     0,   481,     0,   312,   339,
     725,     0,   725,   538,     0,    23,   481,     0,   481,   970,
       0,   987,   483,   481,   481,   481,    32,   484,    81,   444,
     953,   481,   947,   105,   481,    37,   481,     0,   340,     0,
       0,    63,     0,     0,   329,    44,     7,   964,     0,     0,
       0,     0,     0,    77,   340,     0,   984,   522,     0,     0,
       0,   296,   295,     0,     0,   811,     0,     0,   340,     0,
       0,   538,     0,   340,     0,     0,     0,   340,    33,   340,
      22,   597,     0,    21,     0,     0,     0,     0,     0,     0,
       0,   398,   340,    45,   140,     0,     0,     0,     0,     0,
       0,     0,     0,   785,   340,     0,   340,     0,     0,   988,
     989,     0,   339,   340,     0,     0,     0,   597,     0,  1174,
    1173,  1178,  1055,   725,  1180,   725,  1170,  1172,  1056,  1161,
    1164,  1167,   725,   725,   725,  1176,  1169,  1171,   725,   725,
     725,   725,  1109,   725,   725,  1186,  1143,     0,    45,  1195,
    1198,  1201,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    45,    45,  1253,  1231,   610,     4,    20,    20,     0,
       0,    45,     5,     0,     0,     0,     0,     0,    45,    20,
       0,     0,     0,   147,   164,     0,     0,     0,     0,   528,
       0,   528,     0,     0,     0,     0,   528,   222,     6,   486,
     537,   537,   446,   441,     0,   457,   448,   447,   455,    82,
     172,     0,     0,     0,   406,     0,   405,   410,   408,   409,
     407,   381,     0,     0,   351,   382,   354,   384,   383,   355,
     400,   402,   395,   353,   356,   596,   398,   542,   543,     0,
     380,   379,    32,     0,   600,   601,   540,     0,   598,   597,
       0,   544,   597,   562,   546,   545,   598,   549,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,   774,
     775,   773,     0,   771,   761,     0,     0,   435,     0,   323,
       0,   524,   972,   973,   969,    45,   310,   806,   808,   971,
      36,    13,   596,     0,   481,     0,   192,     0,   310,     0,
     184,     0,   707,   705,   841,   925,   926,   805,   802,   803,
     482,   516,   222,   435,   310,   674,   981,   976,   470,   341,
       0,     0,     0,     0,     0,   717,   720,   709,     0,   497,
     680,   677,   678,   451,     0,     0,   500,   982,   442,   443,
     458,   452,   471,   106,   499,    45,   517,     0,   199,     0,
     382,     0,     0,    37,    25,   801,   798,   799,   324,   326,
       0,     0,    45,   965,   966,     0,   698,   696,   684,   681,
     682,     0,     0,    78,     0,    45,   985,   983,     0,     0,
     946,     0,    45,     0,    19,     0,     0,     0,     0,   951,
       0,     0,     0,   497,   523,     0,     0,   929,   956,   597,
       0,   597,   598,   139,    34,    12,   143,   574,     0,   762,
       0,     0,     0,   725,   704,   702,   886,   923,   924,     0,
     701,   699,   957,   399,   514,     0,     0,     0,   907,     0,
     919,   918,   921,   920,     0,   689,     0,   687,   692,     0,
       0,    37,    24,     0,   310,   938,   941,     0,    45,     0,
     302,   298,     0,     0,   575,   310,     0,   527,     0,  1113,
    1108,   527,  1145,  1175,     0,   527,   527,   527,   527,   527,
     527,  1168,   310,    46,  1194,  1203,  1204,     0,     0,    45,
       0,  1018,  1019,     0,   986,   349,     0,     0,     0,     0,
    1233,  1235,  1236,     0,     0,  1239,  1241,  1242,  1243,     0,
       0,  1247,     0,     0,    20,    43,    38,    42,     0,    40,
      17,    46,   310,   132,   134,   136,   110,     0,     0,    20,
     339,   148,   538,   596,   165,   146,   310,   179,   181,   183,
     187,   527,   190,   527,   196,   198,   200,   209,     0,   213,
       0,    45,     0,   449,   424,     0,   351,   364,   363,   376,
     362,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     596,     0,     0,   596,     0,     0,   398,   404,   396,   512,
       0,     0,   515,   568,   569,   573,     0,   565,     0,   567,
       0,   606,     0,     0,     0,     0,     0,   553,   567,   557,
       0,     0,   580,   547,   578,     0,     0,   351,   353,   550,
     584,   583,   552,   675,   310,   697,   700,   703,   706,   310,
     339,     0,   939,     0,    45,   756,   178,     0,     0,     0,
       0,     0,     0,   312,   810,     0,   529,     0,   475,   479,
       0,   469,   596,     0,   194,   185,     0,   321,     0,   208,
       0,   676,   596,     0,   784,   319,   316,   313,   315,   320,
     310,   725,   722,   731,   726,     0,     0,     0,     0,     0,
     723,   709,   725,     0,   788,     0,   498,   539,     0,     0,
       0,    18,   204,     0,     0,     0,   206,   195,     0,   494,
     492,   489,     0,    45,     0,   329,     0,     0,   332,   330,
       0,    45,   967,   381,   915,   962,     0,     0,   960,     0,
       0,    87,    88,    86,    85,    91,    90,   102,    95,    98,
      97,   100,    99,    96,   101,    94,    92,    89,    93,    83,
       0,    84,   197,     0,     0,     0,     0,     0,     0,   297,
       0,   188,   436,     0,    45,   952,   950,   133,   815,     0,
     813,     0,     0,   292,   539,   180,     0,   577,     0,   576,
     287,   287,     0,   757,     0,   725,   709,   933,     0,     0,
     930,   284,   283,    62,   281,     0,     0,     0,     0,     0,
       0,     0,   686,   685,   135,    14,   182,   940,    45,   943,
     942,   146,     0,   103,    47,     0,     0,   693,     0,   725,
     527,     0,  1142,  1112,  1107,   725,   527,  1144,  1187,   725,
     527,   725,   527,   527,   527,   725,   527,   725,   527,   694,
       0,     0,     0,     0,  1215,     0,     0,  1202,  1206,  1208,
    1207,    45,  1197,   849,  1216,     0,  1200,     0,     0,     0,
     993,    45,    45,    45,     0,   390,   391,  1023,     0,  1026,
       0,     0,     0,    45,  1228,     0,     0,     0,    45,  1229,
    1249,  1251,     0,    45,  1230,    28,    37,     0,     0,    39,
       0,    30,   159,   116,   310,   339,   118,   120,     0,   121,
     114,   122,   130,   129,   123,   124,   125,     0,   112,   115,
      26,     0,   310,     0,     0,   144,   177,     0,     0,   222,
     222,     0,   224,   217,   221,     0,     0,     0,   352,     0,
     359,   361,   358,   357,   375,   377,   371,   365,   504,   368,
     366,   369,   367,   370,   372,   374,   360,   373,   378,   596,
     411,   389,     0,   343,     0,   414,   415,   401,   412,   403,
       0,   596,   513,     0,   532,   530,     0,   596,   564,   571,
     572,   570,   599,   608,   603,   605,   607,   604,   602,   563,
     548,     0,     0,     0,   351,     0,     0,     0,     0,     0,
     695,   777,     0,   787,   790,   780,     0,   789,   783,     0,
     781,   782,   779,   772,     0,   429,     0,     0,   506,     0,
       0,     0,     0,   809,   477,   476,     0,   474,     0,   193,
       0,   527,   804,   427,   428,   432,     0,     0,     0,   314,
     317,   176,     0,   596,     0,     0,     0,     0,     0,   710,
     721,   310,   462,   725,   679,     0,   481,     0,     0,   201,
       0,   394,   975,     0,     0,     0,    16,   800,   327,   337,
       0,   333,   335,   331,     0,     0,     0,     0,     0,     0,
       0,   959,   683,    80,    79,   128,   126,   127,   340,     0,
     487,   423,     0,     0,     0,     0,   191,     0,   520,     0,
       0,   725,     0,     0,    64,   527,   505,   599,   138,     0,
     142,    45,     0,   709,     0,     0,     0,     0,   928,     0,
       0,     0,     0,     0,   908,   910,     0,   690,   688,     0,
      45,   945,    45,   944,   145,   340,     0,   502,     0,  1177,
       0,   725,  1179,     0,   725,     0,     0,   725,     0,   725,
       0,   725,     0,   725,     0,     0,     0,    45,     0,     0,
       0,  1205,     0,  1196,  1199,   997,   995,   996,    45,   992,
       0,     0,     0,   350,   596,   596,     0,  1022,     0,  1025,
       0,    45,  1234,     0,     0,     0,  1240,     0,     0,  1248,
      15,    29,    41,     0,   173,   160,   117,     0,    45,     0,
      45,    27,   159,   539,   539,   169,   172,   168,     0,   186,
     189,   214,     0,     0,     0,   247,   245,   252,   249,   263,
     256,   261,     0,     0,   215,   238,   250,   242,   253,   243,
     258,   244,     0,   237,     0,   232,   229,   218,   219,     0,
       0,   425,   351,     0,   387,   596,   347,   344,   345,     0,
     398,     0,   534,   533,     0,     0,   579,   352,     0,     0,
       0,   351,   586,   351,   590,   351,   588,   310,     0,   596,
     518,     0,     0,   974,     0,   311,   478,   480,   172,   322,
       0,   596,   519,     0,   978,   596,   977,   318,   320,   724,
       0,     0,     0,   734,     0,     0,     0,     0,   708,   464,
     481,   501,     0,   203,   202,   381,   493,   490,   488,     0,
     491,     0,   328,     0,     0,     0,     0,     0,     0,   961,
       0,  1007,     0,     0,   422,   417,   948,   949,   719,   310,
     955,   437,   814,   817,   823,   294,   293,     0,   287,     0,
       0,   289,   288,     0,   758,   759,   711,     0,   937,   936,
       0,   934,     0,   931,   282,     0,  1013,  1002,     0,  1000,
    1003,   753,     0,     0,   922,   914,   691,     0,     0,     0,
       0,     0,   300,     0,   299,   307,     0,  1186,     0,  1186,
    1186,  1122,     0,  1116,  1118,  1119,  1117,   725,  1121,  1120,
       0,  1186,   725,  1140,  1139,     0,     0,  1183,  1182,     0,
       0,  1186,     0,  1186,     0,   725,  1061,  1065,  1066,  1067,
    1063,  1064,  1068,  1069,  1062,     0,  1150,  1154,  1155,  1156,
    1152,  1153,  1157,  1158,  1151,  1160,  1159,   725,     0,  1103,
    1105,  1106,  1104,   725,     0,  1133,  1134,   725,     0,     0,
       0,     0,     0,     0,  1217,     0,     0,   850,   994,     0,
    1020,     0,   596,     0,  1024,  1027,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   792,     0,
     111,     0,   173,     0,   146,     0,   171,   170,   267,   253,
     266,     0,   255,   260,   254,   259,     0,     0,     0,     0,
       0,   222,   212,   223,   241,     0,   222,   234,   235,     0,
       0,     0,     0,   278,   223,   279,     0,     0,   227,   268,
     273,   276,   229,   220,     0,   503,     0,   413,   385,   388,
       0,   346,     0,   531,   566,   567,     0,     0,   351,     0,
       0,     0,   776,   770,   786,     0,     0,     0,   525,     0,
     340,   526,     0,   980,     0,     0,     0,   738,     0,   736,
     733,   728,   732,   730,     0,    45,     0,   463,   450,   205,
     334,   336,     0,     0,     0,   963,   958,   131,     0,  1006,
     421,     0,     0,   416,   954,     0,    45,   812,   824,   825,
     830,   834,   827,   835,   836,   831,   833,   832,   828,   829,
       0,     0,     0,     0,   285,     0,     0,     0,     0,   932,
     927,   472,     0,   999,   725,   909,     0,     0,   884,   104,
     306,   301,   303,     0,     0,     0,  1071,   725,  1072,  1073,
      45,  1114,   725,  1141,  1137,   725,  1186,     0,  1070,    45,
    1074,     0,  1075,     0,  1059,   725,  1148,   725,  1101,   725,
    1131,   725,  1209,  1210,  1211,  1219,  1220,    45,  1214,  1212,
    1213,     0,     0,     0,   393,  1238,   896,   897,   898,   895,
     900,   894,   901,   893,   892,   891,   899,   887,     0,     0,
      45,  1237,  1245,  1246,  1244,  1252,  1250,    31,   175,   174,
       0,     0,   119,   113,   107,     0,     0,   161,   596,   166,
       0,   248,   246,   264,   257,   262,   216,   222,   596,     0,
     240,   236,   223,     0,   233,     0,   270,   269,     0,   225,
     229,     0,     0,     0,     0,     0,   230,     0,   426,   386,
     348,   397,     0,   581,   593,   595,   594,     0,   430,     0,
       0,   807,     0,   433,     0,   979,   754,   727,     0,     0,
      45,     0,     0,     0,   842,   968,   843,  1012,     0,  1009,
    1011,   420,   419,     0,     0,   816,     0,   826,     0,   288,
       0,     0,   763,   760,   717,   712,   713,   715,   716,   935,
    1001,  1005,     0,     0,   381,     0,     0,     0,     0,     0,
     309,   308,   521,     0,     0,     0,  1115,  1138,     0,  1185,
    1184,     0,     0,     0,  1060,  1149,  1102,  1132,  1218,     0,
       0,   392,     0,     0,     0,     0,     0,   793,   162,   163,
       0,     0,   239,   596,   241,     0,   280,   228,     0,   272,
     271,   274,   275,   277,   473,     0,   768,   767,   769,     0,
     765,   431,     0,   991,   434,     0,   739,   737,     0,   729,
       0,     0,     0,  1008,   418,     0,     0,     0,     0,     0,
     905,     0,     0,     0,     0,     0,     0,   286,   291,   290,
       0,     0,     0,   998,   911,   912,     0,   840,   885,   885,
     305,   304,  1087,  1086,  1085,  1092,  1093,  1094,  1091,  1088,
    1090,  1089,  1098,  1095,  1096,  1097,     0,  1082,  1126,  1125,
    1127,  1128,     0,  1187,  1077,  1079,  1078,     0,  1081,  1080,
       0,  1021,     0,     0,   888,   794,     0,   172,   265,     0,
       0,   227,   226,     0,     0,   764,   510,     0,     0,     0,
     466,  1010,   822,   821,     0,   819,   725,   854,     0,     0,
       0,     0,     0,   903,   904,     0,     0,     0,     0,   714,
     916,  1004,    45,     0,     0,     0,     0,     0,  1124,  1181,
    1076,    45,   889,     0,     0,     0,   251,   231,   495,   766,
     755,   742,   735,   740,     0,     0,   818,   859,   855,     0,
       0,     0,     0,     0,     0,     0,     0,   846,     0,   467,
     718,     0,     0,   839,    45,    45,   882,  1084,  1083,     0,
       0,     0,   354,   797,   791,   795,   167,     0,     0,   465,
     820,     0,     0,     0,     0,   852,   844,     0,   838,     0,
     902,   853,     0,   845,     0,   917,     0,     0,     0,  1123,
       0,   890,     0,   496,     0,   745,     0,   743,   746,   857,
     858,     0,   860,   862,     0,     0,     0,   847,   468,   913,
     883,   881,     0,   796,   748,   749,     0,   741,     0,   856,
       0,   851,   837,     0,     0,     0,     0,   747,   750,   744,
     861,     0,     0,   865,   906,   848,  1015,   751,     0,     0,
       0,   863,    45,  1014,   752,   867,   866,    45,     0,     0,
       0,   868,   873,   875,   876,  1016,  1017,     0,     0,     0,
      45,   864,    45,    45,   596,   879,   878,   877,   869,     0,
     871,   872,     0,   874,     0,    45,   880,   870
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   206,   379,   207,   831,   743,   208,
     900,   611,   795,   681,   561,   898,   899,   436,   901,  1217,
    1496,   209,   210,   612,  1120,  1121,   211,   212,   213,   571,
    1277,  1278,  1124,  1279,   214,   215,   216,   217,  1150,   218,
     219,  1151,   220,   574,   221,   222,   223,   224,  1554,  1555,
     915,  1566,   934,  1827,   225,   226,   227,   228,   229,   230,
     776,  1161,  1162,   231,   232,   233,   738,  1073,  1074,   234,
     235,   702,   447,   927,   928,  1582,   929,   930,  1865,  1592,
    1597,  1598,  1866,  1867,  1593,  1594,  1595,  1584,  1585,  1586,
    1587,  1839,  1589,  1590,  1591,  1841,  2076,  1869,  1870,  1871,
    1163,  1164,  1468,  1469,  1954,  1702,  1142,  1143,   236,   452,
     237,   841,  1971,  1972,  1734,  1735,  1024,   710,   711,  1047,
    1048,  1036,  1037,   238,   748,   749,   750,   751,  1089,  1430,
    1431,  1432,   392,   369,   399,  1322,  1606,  1323,   874,   996,
     614,   633,   615,   616,   617,   618,  1237,  1076,   967,  1879,
     814,   619,   620,   621,   622,   623,  1327,  1608,   624,  1297,
    1876,  1395,  1376,  1396,  1017,  1133,   239,   240,  1917,   241,
     242,   684,  1029,  1030,   701,   418,   243,   244,   245,   246,
    1080,  1081,  1424,  1886,  1887,  1067,   247,   248,   249,   250,
    1199,   251,   970,  1335,   252,   371,   719,  1413,   253,   254,
     255,   256,   257,   644,   636,   976,   977,   978,   258,   259,
     260,   993,   994,   999,  1000,  1001,  1324,   797,   637,   792,
     556,   261,   262,   263,   705,   264,   721,   722,   265,   759,
     760,   266,   493,   826,   827,   829,   267,   268,   757,   269,
     811,   270,   805,   271,   693,  1064,   272,   273,  2125,  2126,
    2127,  2128,  1689,  1061,   402,   713,   714,  1060,  1654,  1717,
    1908,  1909,  2322,  2323,  2386,  2387,  2405,  2417,  2418,  1722,
    1906,   274,   275,  1704,   665,   800,   801,  1894,  2189,  2190,
    1895,   662,   663,   276,   277,   278,   279,  2040,  2041,  2354,
    2355,   280,   746,   747,   281,   698,   699,   282,   677,   678,
     283,   284,  1139,  1140,  1694,  2115,  2284,  2285,  1937,  1938,
    1939,  1940,  1941,   695,  1942,  1943,  1944,  2338,  1224,  1945,
    1946,  1947,  2287,  2363,  2391,  2392,  2422,  2423,  2440,  2441,
    2442,  2443,  2444,  2455,  1948,  2137,  2304,   807,  1818,  2027,
    2028,  2029,  1949,   819,  1483,  1484,  1966,  1157,  2301,   285,
     286,   287,   288,   289,   290,   291,   292,   788,  1159,  1160,
    1710,  1711,   293,   835,   294,   771,   295,   772,   296,  1136,
     297,   298,   299,   300,   301,  1097,  1098,   302,   754,   303,
     304,   305,   673,   674,   306,   307,  1398,  1644,   707,   308,
     309,   767,   310,   311,   312,   313,   314,   315,   316,  1229,
    1230,   317,  1167,  1718,  1719,  2223,   318,  1682,  2108,  2109,
    1720,   319,  2433,   320,   321,   322,   323,  1238,   324,  1240,
     325,   326,   327,   328,   329,  1200,  1765,   853,  1743,  1744,
    1745,  1769,  1770,  1771,  2257,  1772,  1773,  1746,  2144,  2348,
    2246,   330,  1206,  1793,   331,   332,   333,   334,  1190,  1747,
    1748,  1749,  2252,   335,  1208,  1797,   336,  1196,  1752,  1753,
    1754,   337,   338,   339,  1202,  1787,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,  1758,  1759,   854,  1505,   355,   356,   357,   358,   359,
     864,   865,   866,  1218,  1219,  1220,  1225,  1803,  1804,   360,
     361,   362,   363,   364,   365,   366,   367,   879,   880,   881,
     882,   884,   885,   886,   887,   888,   890,   891,   554
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1909
static const yytype_int16 yypact[] =
{
   -1909,   125, -1909, -1909, -1909, -1909,    47,  4794, -1909, -1909,
   -1909,   152, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,   778, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909,    45, -1909, -1909,   665,   158, -1909, -1909, -1909,    45,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909,    76,    76, -1909, -1909, -1909, -1909, -1909,    76,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
     212, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,    76, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909,   277, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
     305,   386, -1909, -1909, -1909, -1909, -1909,    45, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909,    45, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909,   370,   429,   502,    76, -1909,   295,  1633,   562,   295,
   -1909, -1909, -1909,   612,   670,   697,   719, -1909, -1909, -1909,
     109,   729,    76, -1909, -1909,   806,   814,   817,   820,   596,
     572,   849,   852,   860, -1909,   136, -1909, -1909, -1909,   295,
   -1909, -1909, -1909,   793,    46,  1720,  2000, -1909, -1909,  2841,
   -1909,   862, -1909, -1909,  1098, -1909,   873, -1909,  1557,   873,
     886, -1909, -1909,   892, -1909, -1909, -1909,   901,   920,   936,
     943,   946, -1909, -1909, -1909, -1909,   960,  1042, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909,   972, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,   153,    76,
     981,   992,  1070,   875,    76,    76,   141,    76, -1909,    76,
      76,  1076, -1909,   430,  1101,    76,    76,    76,    76, -1909,
   -1909,    76, -1909,  1103,    76,   931,    76,  1075, -1909, -1909,
   -1909,    76, -1909,  1106,    76, -1909,    76,  1131,   176, -1909,
     931, -1909,    76,    76,    76,    76, -1909, -1909, -1909, -1909,
   -1909,    76, -1909,    76,    76,   562,    76,  1146,   981,    76,
    1170, -1909,    76,    76, -1909, -1909, -1909,  1066,  1177,    76,
      76,  1181,  1201,    76,   981,  1207,  2841, -1909,  1230,  1233,
      76, -1909,  1116,    76,  1090, -1909,  1239,    76,   981,  1257,
    1271, -1909,   875,   981,    76,    76,  1933,   121,    76,   126,
   -1909, -1909,   180, -1909,   184,    76,    76,    76,  1280,    76,
      76,  2841,   127, -1909, -1909,  1288,    76,    76,    76,    76,
      76,  2497,    76, -1909,   981,    76,   981,    76,    76, -1909,
   -1909,    76, -1909,   981,    76,  1297,  1309, -1909,    76, -1909,
   -1909,  1312, -1909, -1909,  1317, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909,  1323, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909,    76, -1909, -1909,
    1340,  1348,  1350,  2841,  2841,  2841,  2841,  2841,  1352,  1354,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,  1084,
     138, -1909, -1909,    76,    76,    76,    76,  1197, -1909, -1909,
    1246,    76,    76, -1909,   649,    76,    76,    76,    76,    76,
     619,    76,  1090,    76,    76,  1146, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909,  1044, -1909, -1909, -1909, -1909, -1909,
   -1909,  2841,  2841,  2841, -1909,  2841, -1909, -1909, -1909, -1909,
   -1909, -1909,  2841,  3150, -1909,    68,  1370, -1909,  1357, -1909,
    1129,  1141,  1367, -1909, -1909,  1368,  2841, -1909, -1909,  1477,
   -1909, -1909,  1362,  1062,  1370, -1909, -1909,   701,   -10, -1909,
    1477, -1909, -1909, -1909,  1384,   424,   100,  2903,  2903,    76,
      76,    76,    76,    76,    76,    76,  1386, -1909,    76, -1909,
   -1909, -1909,   507, -1909, -1909,  1379,    76, -1909,  2841, -1909,
    1160,   925, -1909,  1389, -1909, -1909,  1391,  1401, -1909, -1909,
   -1909, -1909, -1909,  2539,    76,  1397, -1909,    76,  1391,    76,
   -1909,   875, -1909, -1909, -1909, -1909, -1909, -1909,  1405, -1909,
   -1909, -1909, -1909, -1909,  1391, -1909, -1909,  1403, -1909, -1909,
     739,  1778,    76,   754,   134, -1909,  1410,  1241,  2841,  1277,
   -1909,  1412, -1909, -1909,  2841,  2841, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909,    76, -1909,    76,
    1413,   471,    76,   562, -1909, -1909,  1422, -1909,  1423, -1909,
    1417,  1947, -1909,  1427, -1909,    76, -1909, -1909, -1909,  1428,
   -1909,  1411,  3268, -1909,    76, -1909,  5505, -1909,    76,  2841,
   -1909,  1424, -1909,    76, -1909,    76,    76,    76,  1370,  1040,
      76,    76,    76,  1277, -1909,    76,   193, -1909, -1909, -1909,
    1062,   701, -1909, -1909, -1909, -1909, -1909, -1909,   153, -1909,
    1379,  1431,  1410, -1909, -1909, -1909, -1909, -1909, -1909,    76,
   -1909, -1909, -1909,  5505, -1909,   430,  1381,    76, -1909,  1426,
   -1909, -1909, -1909, -1909,  1430,  3354,   802, -1909, -1909,   277,
      76,   562, -1909,    76,  1391, -1909,  1438,  1432, -1909,    76,
   -1909,  1439,  2841,  2841, -1909,  1391,    76,   132,    76,  1161,
    1161,   161,  1161, -1909,  1434,   163,   194,   248,   434,   447,
     450, -1909,  1391,   465, -1909,  1448, -1909,    98,   186, -1909,
    3398,  5505,  3429,  3465,  1449,  5505,    76,    76,   384,   805,
   -1909, -1909, -1909,   266,   809, -1909, -1909, -1909, -1909,   829,
     810, -1909,    76,    76, -1909, -1909, -1909, -1909,   812, -1909,
   -1909,  1247,  1391, -1909, -1909, -1909, -1909,  1440,    76, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909,  1391, -1909, -1909, -1909,
   -1909,  1451, -1909,  1451, -1909, -1909, -1909, -1909,   574, -1909,
     426, -1909,  1447, -1909, -1909,  3546,  1455,  1456,  1456,  1682,
   -1909,  2841,  2841,  2841,  2841,  2841,  2841,  2841,  2841,  2841,
    2841,  2841,  2841,  2841,  2841,  2841,  2841,  2841,  2841,  2841,
   -1909,  1402,  1339,  1450,   101,   442,  2841, -1909, -1909, -1909,
     816,  1095, -1909, -1909, -1909, -1909,   826, -1909,  1864,   634,
    2841,  1460,  1062,  1062,  1062,  1062,  1062, -1909,  1672, -1909,
     424,   424,  1370,  1462, -1909,  2903,  5505,    81,   133, -1909,
    1465,  1466, -1909, -1909,  1391, -1909, -1909, -1909, -1909,  1391,
   -1909,   579, -1909,   153, -1909, -1909, -1909,    76,  3577,    76,
    1468,  2841,  1408, -1909, -1909,    76, -1909,  2841,  3611, -1909,
     838, -1909, -1909,  1443, -1909, -1909,   840, -1909,    76, -1909,
      76, -1909, -1909,  1778, -1909, -1909, -1909, -1909, -1909,  3657,
    1391, -1909, -1909, -1909,  1470,  1472,  1473,  1474,  1475,  1480,
   -1909,  1241, -1909,    76, -1909,  3692, -1909, -1909,    76,  3726,
    3763, -1909,  1481,   842,  1469,  1367, -1909, -1909,    76, -1909,
    1489, -1909,  1476, -1909,    76, -1909,  1371,    74, -1909, -1909,
     288, -1909, -1909,  1492, -1909,  1488,  1498,   843, -1909,    76,
    1485, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
    1490, -1909, -1909,   448,  1491,  1463,  3820,  2601,   -83, -1909,
    1478, -1909, -1909,   854, -1909, -1909, -1909, -1909, -1909,   859,
   -1909,  1483,   863, -1909, -1909, -1909,  2841, -1909,  2035, -1909,
   -1909, -1909,   868, -1909,  1509, -1909,  1241,  1502,  1512,   878,
   -1909, -1909, -1909,  1515, -1909,  1510,  1513,  1503,    76,  2841,
    2841,  2497, -1909, -1909, -1909, -1909, -1909, -1909, -1909,  1516,
    1522, -1909,   505, -1909, -1909,  3906,  3946, -1909,  1511, -1909,
     451,  1517, -1909, -1909, -1909, -1909,   462, -1909, -1909, -1909,
     468, -1909,   472,   499,   508, -1909,   525, -1909,   549, -1909,
    1519,  1521,  1524,  1528, -1909,  1530,  1531, -1909, -1909, -1909,
   -1909, -1909, -1909,  1370,  1529,  1526, -1909,  1532,   -61,   884,
   -1909, -1909, -1909, -1909,  2841,   614,   660, -1909,   895, -1909,
     896,  1534,  1537, -1909, -1909,  1539,  1540,  1541, -1909, -1909,
   -1909,  1542,  1543, -1909, -1909, -1909,   562,    76,   107, -1909,
    1545, -1909,  1556, -1909,  1391, -1909, -1909, -1909,  1549, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909,  1218, -1909, -1909,
   -1909,    76,  1391,   112,  1369, -1909, -1909,    76,    76, -1909,
    1136,   426, -1909,  1560, -1909,  1518,  2841,  2903, -1909,  2841,
    1456,  1456,   584,   584,  1682,   672,  3018,  1820,  5505,  1820,
    1820,  1820,  1820,  1820,  3018,  4106,  1456,  4106,  3859,  1450,
   -1909, -1909,  1550,  1569,  2340, -1909, -1909, -1909, -1909, -1909,
    1571, -1909, -1909,   875,  5505, -1909,  2841, -1909, -1909, -1909,
   -1909,  5505,   173,  5505,  1460,  1460,   792,  1460,   768, -1909,
    1462,  1574,   424,  3977,  1578,  1579,  1581,  2903,  2903,  2903,
   -1909, -1909,    76,  1564, -1909, -1909,  1575,  1410, -1909,   277,
   -1909, -1909, -1909, -1909,  1341, -1909,   915,   875, -1909,   875,
     917,  1587,   929, -1909,  5505,  2841,  2539, -1909,   934, -1909,
     875,  1451, -1909,   717,   752, -1909,   939,  1429,   951, -1909,
    2128, -1909,   134, -1909,  1582,    76,    76,  2841,    76, -1909,
   -1909,  1391, -1909, -1909, -1909,  1359,    76,  2841,    76, -1909,
      76, -1909,  1370,  2841,  1580,  2601, -1909, -1909, -1909, -1909,
     963, -1909,  1583, -1909,  1585,  1588,  1589,  1394,  2841,    76,
      76, -1909, -1909, -1909, -1909, -1909, -1909, -1909,   981,    76,
   -1909,  2647,  2982,  1584,    76,    76, -1909,    76, -1909,   -19,
      76, -1909,  2841,    76, -1909,  1451,  5505, -1909,  1599,    57,
    1599, -1909,    76,  1241,  1602,  2731,    76,    76, -1909,   430,
    2841,   664,  2841,   971, -1909,  1598,   977,  5505, -1909,    31,
   -1909, -1909, -1909, -1909, -1909,   981,    90, -1909,    76, -1909,
     608, -1909, -1909,   200, -1909,   172,   550, -1909,  1125, -1909,
     377, -1909,   195, -1909,    76,    76,    76, -1909,    76,    76,
     465, -1909,    76, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
    1286,  1300,  1287,  5505, -1909,  1450,    76, -1909,    76, -1909,
      76, -1909, -1909,    76,    76,    76, -1909,    76,    76, -1909,
   -1909, -1909, -1909,    76,   848, -1909, -1909,  1604, -1909,  1610,
   -1909, -1909,  1556, -1909, -1909, -1909, -1909,  5505,  2270, -1909,
   -1909, -1909,   482,   469,   469,  1374,  1376, -1909, -1909,  1378,
    1383,  1387,   674,    76, -1909, -1909, -1909, -1909,  1620, -1909,
   -1909, -1909,  1560, -1909,  1622, -1909,   139,  1617, -1909,  1621,
    4021, -1909,  1614,  1616,  1367, -1909, -1909,  4056, -1909,  2841,
    2841,  1095, -1909,  5505,  1477,   424, -1909,   164,  2903,  2903,
    2903,   190, -1909,   221, -1909,   232, -1909,  1391,    76, -1909,
   -1909,  1632,   979, -1909,  1635, -1909,  5505, -1909, -1909, -1909,
    2841, -1909, -1909,  2841, -1909, -1909, -1909, -1909,  5505, -1909,
    1429,  2841,  1623, -1909,  1625,  1626,  4162,  1640, -1909,    65,
      76, -1909,   982, -1909, -1909,  1624,  5505, -1909, -1909,  4056,
   -1909,  1371, -1909,  1371,    76,    76,    76,   997,  1001, -1909,
      76,  1637,  1634,  2841,  4197,  2799, -1909, -1909, -1909,  1391,
    1370, -1909, -1909,  1484,  1646,  5505, -1909,    76, -1909,  1643,
    1644, -1909, -1909,  1420,  1657, -1909, -1909,  1675, -1909,  5505,
    1004, -1909,  1009, -1909, -1909,  4231, -1909, -1909,  1013, -1909,
   -1909,  5505,  1662,    76, -1909, -1909, -1909,  1670,  1677,  1482,
    1629,    76,    76,  1676,  1689, -1909,   561, -1909,  1687, -1909,
   -1909, -1909,  1688, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
     608, -1909, -1909, -1909, -1909,   200,    76, -1909, -1909,  1019,
    1700, -1909,  1701, -1909,  1702, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909,   550, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,  1125, -1909,
   -1909, -1909, -1909, -1909,   377, -1909, -1909, -1909,   195,  1697,
    1699,  1704,   958,  1023, -1909,  1705,  1706,  1370, -1909,  1707,
   -1909,  1713,  1450,  1710, -1909, -1909,  1025,  1059,  1030,  1065,
    1109,  1111,  1112,  1115,  1711,  2841,  2841, -1909, -1909,  1712,
   -1909,  2616,   848,  2304, -1909,  1127, -1909,  5505, -1909, -1909,
   -1909,  1727, -1909, -1909, -1909, -1909,   101,   101,   101,   101,
     101,  1136, -1909,  1721,  1716,  1741,  1136,  1617, -1909,   426,
     139,   117,   117, -1909, -1909, -1909,  1134,  1752,   631,   142,
   -1909,  1751,   139, -1909,  2841, -1909,  1743, -1909,  1367, -1909,
    2340,  5505,  1740, -1909, -1909,   701,  1738,  1749,  1135,  1750,
    1754,  1757, -1909, -1909, -1909,  1764,     0,   875, -1909,    76,
     981,  5505,     0,  5505,  1429,  2841,  1759,  4267,  1137, -1909,
   -1909, -1909, -1909, -1909,  2841, -1909,  1767, -1909, -1909, -1909,
   -1909, -1909,  1156,  1158,  1159, -1909, -1909, -1909,   474, -1909,
    5505,  2841,  2841,  4304, -1909,    76, -1909, -1909,  1646, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
    1746,    57,  1758,  3268, -1909,    76,    76,    76,  2731, -1909,
   -1909, -1909,   664, -1909, -1909, -1909,  2451,    76, -1909, -1909,
    1772,  1788, -1909,    76,    76,  2841, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909,   172, -1909, -1909,
   -1909,  2841, -1909,  2841, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909,    76,    76,  1777,   761, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,  1785,  1787,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,  5505,  5505,
    1165,  1796, -1909, -1909, -1909,  1783,  4345, -1909, -1909, -1909,
     482, -1909, -1909, -1909, -1909, -1909, -1909,  1136, -1909,    76,
   -1909, -1909,  1791,  1789, -1909,  1080,   142,   142,   139, -1909,
     139,   117,   117,   117,   117,   117,  1264,  4400, -1909, -1909,
   -1909, -1909,  2841, -1909, -1909, -1909, -1909,  1967, -1909,    76,
    1808,  1401,    76, -1909,    76, -1909,  4431, -1909,  2841,  2841,
   -1909,  4467,  1565,  2841, -1909, -1909, -1909, -1909,  1167, -1909,
   -1909,  5505,  5505,  2841,  1803, -1909,  1099, -1909,  2841, -1909,
    1801,  1805, -1909, -1909,  1812,  1822, -1909, -1909, -1909, -1909,
   -1909,  1696,  1819,  1168,  1824,  1834,  1186,   910,    76,    76,
   -1909, -1909,  5505,  1071,  1823,   332, -1909, -1909,  1809, -1909,
   -1909,   -30,  4547,  4793, -1909, -1909, -1909, -1909, -1909,  1189,
    1832,   787,    76,    76,  1059,  1847,  1848, -1909, -1909, -1909,
    1369,  1835, -1909,  1450, -1909,   139, -1909,  1264,  1837,   142,
     142, -1909, -1909, -1909, -1909,  5125, -1909,  4056, -1909,  1191,
   -1909, -1909,   875,  1529, -1909,  1429,  5505, -1909,  1605, -1909,
    1846,  5161,   474, -1909,  5505,  2408,  1849,  1852,  1853,  1856,
    1860,  1861,    76,    76,  1867,  1868,  5192, -1909, -1909, -1909,
    2841,    76,    76, -1909, -1909,  1869,    76, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909,  1855, -1909, -1909, -1909,
   -1909, -1909,  1193, -1909, -1909, -1909, -1909,  1842, -1909, -1909,
    1877, -1909,   605,  1879, -1909, -1909,  1881, -1909, -1909,  1871,
    1194,  1264, -1909,  2841,  1967, -1909, -1909,  2841,    76,  2841,
   -1909, -1909, -1909,  5505,  1211, -1909, -1909,  1849,    76,    76,
      76,    76,    76, -1909, -1909,  2841,  2841,  2841,  1228, -1909,
   -1909,  1885, -1909,  1229,  1882,  1235,    76,  2841, -1909, -1909,
   -1909, -1909, -1909,  2841,    76,  1873, -1909, -1909,  5223, -1909,
    5505, -1909, -1909,  1880,  5254,  2408, -1909,   410, -1909,  1890,
    1238,  1245,  1894,  1249,  1887,  1252,  5285,  5316,  1888,  5347,
   -1909,    76,  1833, -1909, -1909, -1909, -1909,  1529, -1909,  5378,
    1586,  5409,  1067, -1909,  1904, -1909, -1909,  2841,  2095, -1909,
   -1909,  1907,  1909,    76,    76, -1909, -1909,    76, -1909,  2497,
   -1909, -1909,  2841, -1909,  2841, -1909,  1897,  1261,  1268, -1909,
    1905, -1909,    76,  5505,    76,  5505,  1270, -1909, -1909, -1909,
   -1909,  1276, -1909,  1910,  1284,  1290,  1292,  5440,  5505, -1909,
   -1909, -1909,  2841, -1909, -1909,  1902,  2095, -1909,    76, -1909,
    2841, -1909, -1909,  1903,  2841,  1293,  2841,  1912, -1909, -1909,
   -1909,  5474,  1294, -1909, -1909,  5505,  1918, -1909,  2841,  2841,
    2841,  1916, -1909, -1909, -1909,  5505, -1909, -1909,   -59,    18,
    1296, -1909,  1925,  1926, -1909, -1909, -1909,  1921,  1921,  1921,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,   556,
    1930, -1909,  1815, -1909,  1313, -1909, -1909, -1909
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1909, -1909, -1909, -1909, -1909,   -22,  1724,  1047, -1909, -1909,
    -676,   -52, -1909, -1909,  -377, -1909,   687, -1909,   -50,  1045,
   -1909, -1909, -1909,  2211,    -2, -1909, -1909, -1909, -1909, -1909,
   -1909,   122,   396,   773, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909,  -157,  -885, -1909, -1909, -1909,   871,   399,  1388,
   -1909,  -206, -1525,   131, -1909, -1909, -1909, -1909, -1909, -1909,
    1393,  -280,  -293, -1909, -1909, -1909,  1385, -1909,  -659, -1909,
   -1909, -1909, -1909,  1266, -1909, -1909,   682, -1246, -1508,  1048,
     393, -1482,  -189,   -82,  1057, -1909,   130,   140, -1763, -1909,
   -1512, -1228, -1509,  -238, -1909,   -60, -1539, -1731,  -744, -1909,
   -1909,   513,   844,   298,  -121,    48, -1909,   537, -1909, -1909,
   -1909, -1909, -1909,  -137, -1909,    30,  -590,   983, -1909,   962,
     609,   629,  -371, -1909, -1909,   926, -1909, -1909, -1909, -1909,
     341,   344,  1939,   824,  -358, -1290,   144,  -428, -1007,   796,
    -563,  -576,  1810,   -64,  1570,  -860,  -982, -1909, -1909,  -613,
    -608,  -234, -1909,  -788, -1909,  -566,  -783, -1096, -1909, -1909,
   -1909,   137, -1909, -1909,  1326, -1909, -1909,  1790, -1909,  1792,
   -1909, -1909,   646, -1909,  -381,     3, -1909, -1909,  1797,  1798,
   -1909,   610, -1909,  -723,  -274,  1260, -1909,  1102, -1909, -1909,
    -207, -1909,  1003,   436, -1909,  4597,  -419, -1092, -1909, -1909,
   -1909, -1909, -1909, -1909,   891, -1909,   440,  -876, -1909, -1909,
   -1909,   359, -1272,  -611,  1060,  -875,  -374,  -436,  -440,   724,
     -31, -1909, -1909, -1909,  1414, -1909, -1909,   989, -1909, -1909,
     961, -1909,  1242, -1908,   893, -1909, -1909, -1909,  1416, -1909,
    1418, -1909,  1415, -1909,  1419, -1008, -1909, -1909, -1909,  -147,
    -184, -1909, -1909, -1909,  -398, -1909,  1138,   673,  -393,   679,
   -1909,   -23, -1909, -1909, -1909,  -328, -1909, -1909, -1909, -1531,
   -1909, -1909, -1909, -1909, -1909, -1408,  -547,   129, -1909,  -186,
   -1909,  1295,  1077, -1909, -1909,  1083, -1909, -1909, -1909, -1909,
    -287, -1909, -1909,  1018, -1909, -1909,  1068, -1909,   198,  1078,
   -1909, -1909,  -196,   647, -1909, -1909, -1909,  -217, -1909, -1909,
     175, -1909,  -771,  -386,  -368, -1909, -1909, -1909, -1462, -1909,
   -1909, -1909,  -173, -1909, -1909,  -291, -1909,  -312, -1909,  -331,
   -1909,  -327, -1699, -1091,  -762, -1909,  -108,  -464,  -985, -1767,
   -1909, -1909, -1909,  -483, -1494,   401, -1909,  -700, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909,  -477, -1437,   650,
   -1909,   168, -1909,  1479, -1909,  1630, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1418,   690, -1909,  1395, -1909,
   -1909, -1909, -1909,  1763, -1909, -1909, -1909,   237,  1726, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
     618, -1909, -1909, -1909,   187, -1909, -1909, -1909, -1909,   -51,
   -1872, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909,   504,   375,  -499, -1325, -1215,
   -1285, -1441, -1429, -1421, -1909, -1420, -1412, -1284, -1909, -1909,
   -1909, -1909, -1909,   360, -1909, -1909, -1909, -1909, -1909,   403,
   -1411, -1409, -1909, -1909, -1909,   358, -1909, -1909,   402, -1909,
     289, -1909, -1909, -1909, -1909,   378, -1909, -1909, -1909, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,
   -1909,   171, -1909,   177,   -88, -1909, -1909, -1909, -1909, -1909,
   -1909, -1909,   950, -1909, -1909, -1909,  -821, -1909,   160, -1909,
   -1909, -1909, -1909, -1909, -1909, -1909, -1909, -1909,   930, -1909,
   -1909, -1909,   924, -1909, -1909, -1909, -1909,   921, -1909
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1187
static const yytype_int16 yytable[] =
{
     405,   696,   670,   812,   820,   821,   822,   823,   685,   968,
     417,   417,   666,   808,  1380,   708,  1236,   425,   972,  1082,
     635,  1678,   580,   582,   635,   723,   791,   726,   587,  1603,
    1285,  1453,   729,   730,   731,  1375,   861,  1002,   936,  1712,
     732,  1835,   783,   734,  1583,   736,   451,  1227,   735,  1819,
     559,  1821,  1465,  1409,   432,  1095,  2110,  1868,  2133,  1071,
    1838,   986,  1588,  1840,  1705,  1179,   419,  1779,   470,   753,
     739,   844,   473,  1915,  1180,  1854,   803,   453,  1816,  1780,
    1616,   998,   998,   960,   997,   997,   764,  1781,  1782,  1357,
     690,   784,  1454,  2060,   468,  1336,  1783,  1785,  1034,  1786,
     780,  -582,  1727,   689,  1699,   785,  -541,  1820,  -561,   793,
    1858,   796,   895,  1900,  1041,  1873,   567,   568,  1015,  1222,
    1356,  1525,   495,  2445,   815,     2,     3,  1563,   397,   416,
    2066,  2067,  1860,   397,   397,    46,   830,    25,   833,  1053,
     586,  -591,    29,   895,   586,   839,  2447,  2073,  1474,   675,
    1434,  -527,   553,  -591,  1860,  1861,  1862,  1236,   659,   896,
     660,  2254,  1486,     8,    47,    48,   975,   368,    74,   586,
     573,   586,  -592,   400,  -339,  2448,  1326,  1326,   562,  2074,
    1394,  1766,  1329,  1776,  -592,  1789,   416,  1795,  -563,   979,
     634,   725,  1054,   981,   634,   798,   962,  -582,  -585,   400,
     988,    96,   586,   987,    50,   416,   989,  1226,   588,  1756,
    -585,  1146,  1922,  1923,  1924,   986,  -561,   716,    90,   416,
    1055,  1768,  1774,  1778,  1784,  1791,  1792,   416,    95,  -589,
     416,   109,   635,   569,  1700,  2449,   416,  -137,  1455,  1728,
    -587,  -589,  -141,   -61,  1177,  1813,   416,  -541, -1111,  -591,
     609,   971,  -587,  1153,  1526,  1187,   586,  1527,  2255,  2446,
    1056,   609,  1732,  1436,   590,  -527,  1863,   416,   416,  2256,
     416,  1057,  1209,   905,   121,     4,   435, -1136,  1096, -1058,
    -592,  -339,   416,   917,   918,   919,   920,  -339,  1863,  -563,
     802,  1767,   491,  1777,  2172,  1790,  1494,  1796,   591,  1058,
     921,   416,  -563,  1031,   118,   416,  -585,  1245,  1026,   416,
   -1147,   122,  1262,   416,   961,   416,   661,   664,  1062,  1916,
     501,  2065,   671,   672,   676,   672,  1286,   680,   682,  1670,
    2110,   688,  1158,   692,   694,   694,   697,  -589,  -582,   700,
    2179,  2180,   704,  1616,   700,  1842,  1844,  1779,  -587,   715,
    1148,  2063,   720,  1147,   700,  1149,   700,  -561,  1330,  1780,
     417,   700,   700,   700, -1163,   741,  1083,  1781,  1782,   700,
    2229,   733,   700,  1016,   700,  2061,  1783,  1785,  -137,  1786,
     744,   745,     5,  -141,   -61,   550,  1737,   756,   758, -1111,
    -591,   763,  1059,   778,   502,   635,  1035,  2264,   770,   635,
     786,   774,   634,   986,  1155,   986,   635,  1426,  1568,  1493,
    1662,  1135,   986,   787,  1360,   728,   794,  1491, -1136,  1361,
   -1058,  -592,   715,   804,   806,   806,  2248,   810,   787,   998,
    -563,  1677,  1354,   816,   818,   818,   818,   818,   818,   991,
     828,  1291,   586,   832,   551,   834,   770,  -585,  1609,   837,
    1766, -1147,   840,   686,  1175,   586,   845,  1434,   586,   586,
    1401,  2396,  1421,  1776,  1020,  1706,  1751,   687,  1485,  1789,
     586,  1833,  1834,  1795,   962,  1246,   586,  1739,  -589,  1716,
     586,  2107,  1622,  1624,  1626,   862,  2388,  1192,   863,  -587,
    1768,  1774,  1145,  1283,  1247,  1564,  1435,  1078,  1573,  1574,
     878,   883,   889,  1778,  1784, -1163,  1328,   586,   897,  1791,
    1792,   902,   903,   904,   688,  1013,   586,   552,   907,   910,
     911,  1643,  2013,   916,   688,   688,   688,   688,  1014,  2177,
    2136,   924,   925,   586,  2388,   892,   893,  1174,  1838,  1284,
    1176,  1840,  1344,  1345,  1346,  1347,  1348,   908,  2123,  2159,
   -1166,  2174,   555,   416,  1814,   416,   635,   586,  2361,   416,
    1767,  1579,  2249, -1100,   962,   634, -1130, -1110,  1737,   634,
    1436,   416,   986,  1777,  1579,  1241,   634,   560, -1135,  1790,
     581,   992,  1289,  1796, -1057,  1738,  1319,  1975, -1146,   941,
    2362,   609,  1242,   942,  1088,  1445,  1446,   704,  1004,   756,
     810,   804,   692,  1009,   579,  1583,   834,  1011,   962,  -527,
    2059,  1290,  1210,  1211,   688, -1162,  2250,  -382,  1580,  -527,
     563,   957,  1363,  1588, -1165,  1022,  2312,  2251,  1447,  1534,
    2193,  1580,   700,  -527,  1760,  1033,  2271,   688,  -230,   982,
    1189, -1099,   686,   983,  1195,  1212,  1364,  2071,  2072,  1201,
     630,   631,  1205,  1207,   912,  1342,   687,   984,   971,  1739,
    1050,  1365,  1740,  -383,   913, -1129,  1366,  1367,  1397,  1716,
    1581,   985,   397,  1368,  1556,  1535,  1236,   941,   564,  1651,
     398,   942,  1851,  1581,  2447,  1072,  1601,  1077,   943,   944,
    1079, -1166,  1562,  1799,  1800,  1801,  1272,  1805,  1806,  1273,
    1082,  2263,  1090,  1093, -1100,   565,   982, -1130, -1110,   957,
     983,  1852,  1122,  2448,  1287,  1123,  1288,   630,   631, -1135,
    -382,  1129,  1128,  1130,   984, -1057,   634,   566,  1137, -1146,
    1141,   998,   960,   688,   997,  1336,  1602,   572,   985,  1095,
    1095,  1737,  2315,  1622,  1624,  1626,   661,  1043,   635,   635,
     635,   635,   635,  2461,  2463,  -383, -1162,  1093,  1738,  1663,
    1044,  1664,  1051,   688,  -387, -1165,  2467,   963,   986,   986,
     986,   986,   986,   982,  1905,  1052,   966,   983,   688,  1213,
    1214,   688, -1099,  1215,  1216,  -790,  -790,  1183,  1182,  2303,
    -385,   998,   998,   998,  1621,  1623,  1625,   982,  2335,  1737,
     589,   983,   966,  1223,  1223,   985, -1129,  1369,   630,   631,
    1171,  2059,   778,  1243,   575,  1761,  1738,  1248,  1253,  1228,
    1258,  1658,   576,  1172,  1331,   577,  1244,  2331,   578,   985,
    1249,  1254,  1739,  1259,  1337,  1740,   370,  1332,  1370,  1762,
    1255,   832,   376,  1485,  2347,  1485,  1386,  1338,  1390,  1763,
    1418,  1440,   383,  2333,  1764,   385,  1280,   583,   388,  1387,
     584,  1391,  1457,  1419,  1441,   394,  1825,  1460,   585,   401,
    2330,  1463,  1257,   404,  1826,  1458,  1013,   625,  1292,  1550,
    1461,  1295,  1371,  2269,  1464,  2427,  1477,  1281,   640,  1471,
    1739,   423,  1528,  1740,   648,   427,   428,  2434,  1741,  1478,
     649,   433,   434,  1536,  1538,  1529,  1742,   439,   440,   650,
     441,   442,   443,   444,  2088,   445,  1537,  1539,   634,   634,
     634,   634,   634,  1629,   454,  1234,   992,   992,   651,   458,
    2395,   460,  2016,   586,  2017,   463,  1630,  1043,  1633,   467,
    -527,   469,  1331,  2018,   652,  2019,  2394,  1641,   475,  2047,
    1635,   653,   479,   778,   654,  1638,   482,  1611,   484,  1645,
    1642,   661,  1612,  1614,  1374,   492,   494,  1378,   655,   496,
     497,  1671,  1646,   676,  1950,   503,   778,   504,   638,  1723,
     658,   508,   646,  1501,  1672,  1234,   697,  1390,   397,  1504,
    1234,  2188,  1724,  1507,  1569,  1509,  1507,  1507,  1726,  1511,
    1898,  1513,  1882,  1919,  1609,  1234,  1631,   667,   535,  1440,
     537,  1411,  1958,  1655,  1422,  1657,   720,  1477,  1925,  1639,
    2089,  1962,  1926,  1485,   669,  1959,  2094,  1987,  1643,  1650,
    1960,  2007,   745,  1522,  1963,  1661,  1236,  1892,  2030,   416,
    1988,  1437,  1394,  -384,  2008,   613,  2015,   758,  1134,   656,
     657,  2031,   998,   998,   998,  1888,  1623,  1625,  1326,  1326,
    1326,  1326,  1326,  2051,  2052,  2053,  2054,  2055,  2020,  2021,
     962,  2022,  2023,  1723,   752,  -850,  2232,   790,   630,   631,
     706,  2016,   709,  2017,  1459,   668,  2032,  2233,  2234,   604,
    1680,   683,  2018,  2235,  2019,  2236,  2071,  2072,   606,  1934,
    1333,  2176,  2024,   627,  2237,   599,  2238,   628,  2239,   600,
     601,   602,   603,   629,   630,   631,   691,  1477,   703,  1723,
    1460,   718,   604,  1460,   773,   604,   607,   775,  1489,   605,
    2033,   606,  2034,  2035,   606,  2048,  2036,  1731,  1193,  1194,
    2206,  1197,  2068,  -585,  2025,  2099,   724,   641,  2049,   645,
     647,  1572,  1573,  1574,   608,  2069,  1877,  2026,  2100,   607,
    1812,   737,   607,  1575,  1522,  1250,  1522,  1522,  1251,  1252,
    1727,  1520,  1576,  2165,  1885,  2202,  1171,  2104,  2188,  2105,
    2106,  1530,  1531,  1532,  1640,   742,  2166,   608,  2203,  2225,
     608,   632,   755,   878,  1477,  1577,   761,  1522,   883,  2274,
    1578,  2307,  2068,   889,   906,  1551,   897,  2227,   894,  1760,
    2260,   609,  2275,  2298,  2308,  2317,   762,  2020,  2021,  2325,
    2022,  2023,   765,   712,   416,  1559,  1560,   632,  1579,  1561,
    2240,  1880,  2326,  2241,  2207,   688,  1234,  1477,  1976,  1292,
    1978,  1979,   766,  2345,   609,   768,  1440,   609,   769,  2340,
    2343,  2024,  1983,  1522,   777,  1896,  2346,  1477,  1697,  2365,
    1723,   975,  1990,   610,  1992,  2079,  2366,  1902,  1434,  2030,
    2368,  1904,   781,  2370,  2005,  2006,  2030,   813,  2406,  1918,
    2071,  2072,  2400,   933,  2408,  1580,   782,   825,   992,  2401,
    2208,  2407,  1440,  2025,  1568,   809,   610,  2409,  1477,   610,
    1171,  1234,  2430,   817,  2450,  2411,  2026,  1728,  2209,   986,
    1627,  2412,   842,  2413,  2426,  2431,  1737,  2451,  2242,  2277,
    2210,  1605,  2211,  2212,   843,  2213,   838,   846,  2214,  2181,
    2182,  2183,   848,  1738,  2466,  1843,  1845,  1581, -1186,   870,
     871,   872,   873,   875,  1889,  1890,  1891,   597,   598,  1350,
    1351,  1822,  1823,  1653,  1653,   867,  1653,  2456,  2457,  2377,
    2378,  1203,  1204,   868,   700,   869,  1072,   876,  1072,   877,
     909,  1665,   963,   962,  1565,   964,  2243,  2244,  2245,   599,
     635,  1436,   966,   600,   601,   602,   603,   965,   980,   969,
    1761,  1690,   990,  1010,   798,  2415,   604,   935,   937,   938,
    1019,   939,  1688,   605,  1021,   606,  1023,  1739,   940,  1025,
    1740,  1141,  1032,  1038,  1762,  1741,  1063,  1701,  1042,  2215,
    1068,  1703,   813,  1742,  1763,   400,  1066,   688,   960,  1764,
    1084,  1085,  1086,   607,  1736,  1091,  1099,  1100,  1154,  1127,
    1729,  1168,  1730,  1165,  1733,  1169,  1178,  1184,  1192,  1198,
    1223,  1223,  1223,  1181,  1223,  1223,  1221,  1234,  1807,   586,
    1260,   608,  1296,  1299,  1018,   942,  1320,  1802,  1321,   983,
    1352,  -342,   778,  1358,  1359,  1381,  1223,  1420,  1228,  1028,
    1389,  1449,   973,  1379,  1263,  1403,   974,  1404,  1405,  1406,
    1407,  1817,   790,   630,   631,  1408,  1417,  1423,   416,  -929,
    1429,  1824,  1425,  1438,   604,  1439,  1443,  1049,  1123,  1462,
    1831,  1444,  1448,   606,  1065,  1456,  1472,  1475,   609,  1476,
    1069,  1070,  2300,  1479,  1490,  1480,  2090,  1264,  1481,  1482,
    1492,  1853,  1499,  1265,  1514,   975,  1515,  1522,  1502,  1516,
     717,   607,  2092,  1517,  1864,  1518,  1519,  1523,  2079,  1540,
     634,   992,  1541,  1524,  1543,  1544,  1545,  1547,  1548,  1266,
    1553,   912,   643,  1665,  1558,  1126,  1665,  1665,  1665,   608,
     610,  1604,   629,   630,   631,  1596,  1893,  1605,  1610,   368,
    1599,  2135,  1615,  1267,   604,  1268,  1618,  1619,  1095,  1620,
     398,  2334,  1485,   606,  1634,   975,  1628,  1651,  1660,  1673,
    1674,  1668,  1435,  1675,  1676,  1687,   632,  1698,   700,  1707,
    1223,  1223,  1223,  1725,  1809,  1810,  1811,  1830,  1269,  1828,
    1846,   607,  1847,  1270,  1848,  1856,   609,  1271,  1927,  1849,
    1859,  1272,  1872,  1850,  1273,  1877,  1874,  1878,  1185,  1186,
    1897,  2375,  1899,   975,  1910,  1079,  1911,  1912,  1914,   608,
    -494,   847,  1928,   849,  1936,  1929,  1274,  1935,  1952,  1953,
     850,   851,   852,  2393,  1095,  1956,   855,   856,   857,   858,
    1275,   859,   860,  2228,  2170,  1955,  1276,   982,   610,  1969,
    1970,   983,  1957,  1964,  2173,  1967,   632,   941,   630,   631,
    1728,   942,  1968,  1349,  1973,   984,    25,  1974,   943,   944,
    1727,    29,  1977,  1980,  1986,   946,   609,   948,  2393,   985,
     950,   951,   952,   953,   954,  1989,  1991,  1993,  2002,   957,
    2003,  2057,  2011,    47,    48,  2004,  2009,  2010,  2012,  2293,
    2294,  2014,  2037,  2042,  1282,  2050,  -381,  1300,  1301,  1302,
    1303,  1304,  1305,  1306,  1307,  1308,  1309,  1310,  1311,  1312,
    1313,  1314,  1315,  1316,  1317,  1318,  2058,   557,   610,  2070,
    2075,  2081,   813,  2078,  2082,    13,    14,  1334,    15,    16,
    2083,  2084,  2118,    20,  1341,  2085,  1343,    90,  2086,  2087,
    2097,    23,  2103,  1045,  2120,  1046,    27,    95,   599,    30,
    2138,  1353,   600,   601,   602,   603,  2139,    37,  2161,    38,
    2162,    40,  2163,  2167,  2168,   604,  -224,  2062,  1864,  1864,
    1864,  2329,   605,  2332,   606,  2175,  2192,   875,  2205,  2200,
    1864,  2276,  2218,  1384,    59,   941,  2219,  2220,  2222,   942,
    2221,  -841,   778,   121,  1362,    70,   943,   944,   778,  1049,
    2224,  2226,   607,   946,  2247, -1187,  2253,   676, -1187, -1187,
   -1187, -1187, -1187,  2261,  2265,  2266,  2268,   957,  2272,    85,
    2278,  2279,  2306,  2310,  2286,  2102,   558,  2288,  2289,  1339,
     608,  2290,    93,  1340,   599,  2291,  2292,   150,   600,   601,
     602,   603,  2295,  2296,  2302,  2311,  2116,  2313,  2314,  2344,
     102,   604,  2316,  2341,  2356,  2358,   104,  2364,   605,  1701,
     606,  2367,  2369,  1893,   108,  2124,   110,   416,   112,  2373,
     114,  2376,  2382,  2380,  2389,  2134,  2390,   119,  2399,  2416,
    2402,  2140,  1733,  1452,  2424,  2410,  2432,   609,   607,  2428,
    2145,  2437,  2452,  2453,   130,   131,  2454,  2465,   789,  2151,
    1256,  1156,  1466,  2447,   570,  1552,  1261,  1223,   790,   630,
     631,  2121,   143,  2043,  1829,  1495,   608,  1802,  1433,   596,
     604,  1832,   914,  2044,  2267,   875,  1487,   825,  1039,   606,
     926,  1571,  2186,   155,  1451,   923,   156,   599,  1293,   610,
    2164,   600,   601,   602,   603,  1857,  2270,  1294,  2178,  2064,
    2171,  2056,  1714,   416,   604,  1470,  1951,   607,  2217,  2119,
    1696,   605,  2231,   606,  2141,  1399,  1382,  1853,  1632,  1647,
      25,  1428,  1920,   609,   431,    29,  1864,  1921,  1864,  1864,
    1864,  1864,  1864,  1864,  2080,   608,  2464,   779,  1223,  1040,
    1533,   607,  1637,  1667,   592,  1388,   593,    47,    48,  2093,
     982,   594,   595,  1144,   983,    13,    14,  1883,    15,    16,
    2198,   630,   631,    20,  1884,  1355,  1467,  1414,   984,   608,
    1442,    23,   632,  1003,  1488,   610,    27,  1005,  1007,    30,
    1006,  1173,   985,  1008,  2299,  1649,  2197,    37,  2419,    38,
    1567,    40,   609,  1652,  2122,   806,  2230,  1970,  2319,  1557,
    1373,    90,  1600,  1152,  1372,  2403,   416,  2091,  2262,  1223,
    1716,    95,  1427,  1383,    59,   599,  1392,  1692,  2360,   600,
     601,   602,   603,  2117,  2328,    70,   609,  2420,  2436,  2458,
    1607,  2305,   604,  1864,  1965,  2460,  2129,  1713,   836,   605,
    1679,   606,  1613,  1045,   610,  2384,   727,  1012,   599,    85,
     679,  2095,   600,   601,   602,   603,  1808,   121,  1092,  2130,
    1995,  2281,    93,  1982,  1999,   604,  2001,  1985,  2150,   607,
     818,   818,   605,  2148,   606,  2309,  1997,  2158,   610,  2124,
     102,  1521,  1546,  1542,  1549,     0,   104,     0,  1087,     0,
       0,  1636,  1028,     0,   108,     0,   110,   608,   112,  1402,
     114,   150,   607,     0,     0,     0,  1648,   119,     0,     0,
    1410,     0,     0,  1656,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   875,   130,   131,     0,     0,     0,  1666,
     608,  1669,     0,     0,   416,  1223,  2321,     0,     0,     0,
       0,     0,   143,     0,   875,     0,  1093,     0,  1093,   740,
       0,     0,  1223,     0,   609,     0,     0,  1684,     0,  2352,
       0,     0,  2342,   155,     0,     0,   156,   416,  1695,     0,
       0,  2350,  2353,     0,     0,     0,     0,   740,     0,     0,
       0,  1709,     0,     0,   740,  1836,  1715,   609,  1721,     0,
     599,     0,   799,     0,   600,   601,   602,   603,     0,     0,
       0,     0,     0,  1473,  1817,  1817,   610,   604,     0,     0,
       0,     0,     0,     0,   605,     0,   606,     0,     0,  2045,
       0,     0,     0,     0,   599,     0,     0,     0,   600,   601,
     602,   603,     0,     0,     0,     0,     0,  1500,     0,   610,
    2353,   604,  2404,  1503,   607,     0,     0,  1506,   605,  1508,
     606,     0,     0,  1510,     0,  1512,     0,  1451,     0,     0,
     599,     0,     0,     0,   600,   601,   602,   603,     0,     0,
       0,     0,   608,     0,  1837,     0,     0,   604,   607,     0,
       0,     0,     0,     0,   605,     0,   606,     0,     0,     0,
       0,     0,  2438,     0,     0,     0,     0,  2439,     0,     0,
       0,   922,     0,     0,     0,     0,   608,     0,     0,   416,
    2439,     0,  2459,  2462,   607,  1881,   813,  1334,     0,     0,
       0,     0,     0,  2282,     0,  2462,     0,     0,   599,   609,
       0,     0,   600,   601,   602,   603,     0,     0,     0,     0,
       0,     0,   608,   416,     0,   604,  1901,     0,     0,  1903,
       0,     0,   605,     0,   606,     0,     0,  1907,     0,     0,
       0,     0,     0,   609,     0,   740,     0,     0,   824,     0,
       0,   599,     0,     0,     0,   600,   601,   602,   603,   416,
       0,   610,   607,     0,     0,     0,     0,     0,   604,  1930,
       0,  1933,     0,     0,     0,   605,     0,   606,     0,   609,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     608,     0,     0,     0,   824,   610,   975,   599,     0,     0,
       0,   600,   601,   602,   603,   607,     0,     0,     0,     0,
       0,     0,     0,     0,   604,     0,     0,     0,     0,  2132,
       0,   605,     0,   606,     0,     0,     0,   416,     0,     0,
       0,   610,     0,   608,     0,     0,  1027,  1075,     0,   599,
       0,  1659,     0,   600,   601,   602,   603,   609,     0,     0,
       0,   607,     0,     0,     0,  1094,   604,     0,     0,     0,
       0,     0,     0,   605,     0,   606,     0,     0,  1125,     0,
     416,     0,     0,     0,     0,     0,  1131,  1132,     0,   608,
       0,  1138,     0,     0,     0,     0,     0,     0,     0,  1693,
     609,     0,     0,   607,     0,     0,     0,     0,  1451,   610,
       0,   599,     0,     0,     0,   600,   601,   602,   603,  1094,
       0,  2038,  2039,     0,     0,     0,   416,  1166,   604,  2046,
       0,   608,     0,     0,     0,   605,     0,   606,     0,  1750,
       0,     0,  1755,     0,     0,  1775,   609,  1788,     0,  1794,
       0,  1798,   610,     0,  1683,     0,  1188,   599,  1191,     0,
    1263,   600,   601,   602,   603,   607,     0,     0,   416,     0,
    2077,     0,     0,     0,   604,     0,  1607,   740,   740,     0,
       0,   605,     0,   606,     0,     0,  1235,  1239,   609,     0,
       0,     0,     0,   608,     0,     0,     0,     0,   610,     0,
       0,  2096,     0,  1264,     0,     0,     0,     0,     0,     0,
    2101,   607,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2111,  2112,     0,
     416,     0,     0,     0,     0,  1266,     0,     0,  1708,   608,
     610,   599,     0,     0,     0,   600,   601,   602,   603,     0,
     609,     0,     0,     0,  1709,     0,     0,     0,   604,  1267,
       0,  1268,   825,     0,     0,   605,     0,   606,     0,     0,
       0,  2142,     0,     0,  1325,  1325,   416,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2152,     0,  2153,
       0,     0,     0,     0,  1269,   607,   609,     0,     0,  1270,
     740,   740,   610,  1271,     0,     0,  1932,  1272,     0,   599,
    1273,     0,     0,   600,   601,   602,   603,     0,     0,     0,
       0,     0,     0,   608,   959,     0,   604,  1235,     0,     0,
       0,     0,  1274,   605,     0,   606,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1275,     0,   610,     0,
    1393,   599,  1276,     0,     0,   600,   601,   602,   603,     0,
     416,     0,     0,   607,     0,     0,     0,     0,   604,     0,
       0,     0,     0,     0,     0,   605,     0,   606,  2185,     0,
     609,     0,     0,  2187,     0,  1981,     0,     0,   740,     0,
    1984,   608,     0,     0,  2196,  1907,     0,     0,     0,  2201,
       0,     0,     0,  1994,     0,   607,     0,     0,     0,  2204,
       0,     0,     0,   599,  2216,     0,     0,   600,   995,   602,
     603,     0,     0,     0,     0,  1996,     0,     0,   416,     0,
     604,  1998,   610,   608,     0,  2000,     0,   605,     0,   606,
       0,     0,     0,     0,     0,     0,     0,     0,   609,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1567,   607,     0,     0,
     416,     0,     0,  1119,     0,     0,     0,   959,  1094,     0,
       0,     0,     0,     0,     0,     0,     0,   941,     0,  1685,
     609,   942,   599,     0,     0,   608,     0,     0,   943,   944,
     610,  2283,     0,  1686,   945,   946,   947,   948,     0,     0,
     950,   951,   952,   953,   954,   955,   875,   956,     0,   957,
     958,     0,     0,   941,   959,     0,     0,   942,     0,     0,
       0,     0,   416,     0,   943,   944,   959,     0,     0,     0,
     945,   946,   610,   948,     0,     0,   950,   951,   952,   953,
     954,     0,   609,   956,     0,   957,   958,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2318,
    2187,     0,     0,  2320,     0,  2324,     0,     0,     0,     0,
       0,   959,   959,   959,   959,     0,   959,     0,     0,     0,
       0,  2336,  2337,  2339,     0,     0,     0,     0,  1570,     0,
       0,     0,  2131,  2349,   610,     0,     0,     0,     0,  2351,
       0,     0,     0,     0,     0,  2143,     0,     0,     0,     0,
    2146,  2283,     0,  2147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2154,     0,  2155,     0,  2156,     0,  2157,
       0,     0,     0,     0,     0,     0,   959,     0,   959,   959,
     959,   959,     0,  2383,  2385,   941,     0,     0,     0,   942,
     599,     0,   740,     0,     0,   825,   943,   944,  2397,     0,
    2398,     0,   945,   946,   947,   948,   949,     0,   950,   951,
     952,   953,   954,   955,     0,   956,     0,   957,   958,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   875,     0,
       0,     0,  2385,     0,     0,     0,  2421,   959,     0,     0,
    2425,     0,  1721,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1721,  2435,  2421,     0,  1075,   959,
    1075,     0,     0,     0,     0,     0,     0,     0,     0,   959,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1094,
    1094,     0,     0,     0,     0,     0,     0,     0,     0,  1681,
     959,     0,     0,     0,     0,   740,     0,  1691,     0,     0,
    1138,     0,     0,  1101,     0,     0,   959,  1102,   599,     0,
     959,   959,   799,     0,  1103,  1104,  1094,  1094,     0,     0,
    1105,  1106,  1107,  1108,     0,     0,  1109,  1110,  1111,  1112,
    1113,  1114,  1115,  1116,     0,  1117,  1118,     0,   740,     0,
       0,     0,     0,     0,     0,  1757,     0,     0,     0,     0,
       0,     0,     0,     0,   740,   740,   740,     0,   740,   740,
       0,     0,   740,     0,     0,     0,     0,   959,     0,     0,
       0,     0,     0,     0,     0,     0,  1235,     0,  1815,     0,
     740,     0,     0,  1094,  1094,  1094,     0,  1138,  1138,   941,
       0,  1170,     0,   942,   599,     0,     0,     0,     0,     0,
     943,   944,     0,     0,     0,     0,   945,   946,   947,   948,
       0,     0,   950,   951,   952,   953,   954,   955,     0,   956,
       0,   957,   958,  1855,     0,     0,   959,   959,     0,     0,
       0,     0,     0,   941,     0,     0,  1231,   942,   599,     0,
       0,     0,     0,     0,   943,   944,     0,     0,     0,     0,
     945,   946,   947,   948,  2327,   740,   950,   951,   952,   953,
     954,   955,     0,   956,   941,   957,   958,  1232,   942,   599,
       0,     0,     0,     0,     0,   943,   944,     0,     0,     0,
       0,   945,   946,   947,   948,     0,     0,   950,   951,   952,
     953,   954,   955,     0,   956,     0,   957,   958,     0,     0,
     941,     0,     0,  1233,   942,   599,     0,     0,     0,     0,
       0,   943,   944,     0,   740,   740,   740,   945,   946,   947,
     948,     0,     0,   950,   951,   952,   953,   954,   955,     0,
     956,     0,   957,   958,     0,     0,     0,     0,     0,     0,
       0,   959,   959,   959,   959,   959,   959,   959,   959,   959,
     959,   959,   959,   959,   959,   959,   959,   959,   959,   959,
       0,     0,     0,  1094,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   959,     0,     0,     0,     0,
       0,   941,   959,     0,   959,   942,   599,     0,     0,     0,
       0,     0,   943,   944,   959,     0,     0,  1298,   945,   946,
     947,   948,     0,     0,   950,   951,   952,   953,   954,   955,
       0,   956,   941,   957,   958,     0,   942,   599,     0,     0,
       0,     0,     0,   943,   944,   959,     0,     0,  1377,   945,
     946,   947,   948,     0,     0,   950,   951,   952,   953,   954,
     955,     0,   956,     0,   957,   958,   941,     0,  1385,     0,
     942,   599,     0,     0,     0,     0,     0,   943,   944,     0,
       0,     0,     0,   945,   946,   947,   948,     0,     0,   950,
     951,   952,   953,   954,   955,     0,   956,     0,   957,   958,
       0,     0,     0,     0,     0,     0,  1325,  1325,  1325,  1325,
    1325,     0,   941,   959,  1400,     0,   942,   599,     0,     0,
       0,     0,     0,   943,   944,     0,     0,   959,     0,   945,
     946,   947,   948,     0,     0,   950,   951,   952,   953,   954,
     955,     0,   956,     0,   957,   958,     0,   941,   959,     0,
       0,   942,   599,     0,     0,     0,  1235,     0,   943,   944,
       0,     0,  1393,  1412,   945,   946,   947,   948,     0,     0,
     950,   951,   952,   953,   954,   955,     0,   956,     0,   957,
     958,   941,     0,     0,     0,   942,   599,     0,     0,     0,
       0,     0,   943,   944,   959,  2114,     0,  1415,   945,   946,
     947,   948,     0,     0,   950,   951,   952,   953,   954,   955,
       0,   956,     0,   957,   958,     0,   799,     0,   941,     0,
       0,     0,   942,   599,     0,     0,     0,  1094,   959,   943,
     944,     0,     0,     0,  1416,   945,   946,   947,   948,     0,
       0,   950,   951,   952,   953,   954,   955,  2149,   956,     0,
     957,   958,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   959,     0,     0,     0,     0,     0,     0,   959,     0,
       0,   740,  2160,     0,   959,   941,     0,     0,     0,   942,
     599,     0,     0,     0,     0,     0,   943,   944,     0,     0,
       0,  1450,   945,   946,   947,   948,     0,   959,   950,   951,
     952,   953,   954,   955,     0,   956,     0,   957,   958,   959,
       0,     0,     0,     0,   941,     0,     0,   959,   942,  1855,
       0,     0,     0,     0,     0,   943,   944,   959,     0,     0,
     959,   945,   946,   947,   948,     0,     0,   950,   951,   952,
     953,   954,   955,     0,   956,   959,   957,   958,     0,  2191,
       0,     0,   740,     0,  2194,     0,   959,     0,     0,     0,
       0,   941,     0,     0,     0,   942,   599,     0,     0,     0,
     959,     0,   943,   944,     0,     0,   959,  1497,   945,   946,
     947,   948,   959,     0,   950,   951,   952,   953,   954,   955,
       0,   956,     0,   957,   958,     0,     0,     0,     0,     0,
       0,   941,     0,     0,     0,   942,   599,     0,     0,     0,
       0,     0,   943,   944,     0,     0,     0,  1498,   945,   946,
     947,   948,   740,   740,   950,   951,   952,   953,   954,   955,
       0,   956,   941,   957,   958,     0,   942,   599,     0,     0,
       0,     0,     0,   943,   944,     0,     0,     0,  1617,   945,
     946,   947,   948,     0,     0,   950,   951,   952,   953,   954,
     955,     0,   956,     0,   957,   958,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   941,     0,     0,     0,
     942,   599,  1094,     0,     0,     0,  1094,   943,   944,     0,
       0,     0,  1875,   945,   946,   947,   948,     0,   959,   950,
     951,   952,   953,   954,   955,     0,   956,     0,   957,   958,
       0,   941,     0,  1685,     0,   942,   599,     0,     0,     0,
       0,     0,   943,   944,     0,     0,     0,     0,   945,   946,
     947,   948,     0,     0,   950,   951,   952,   953,   954,   955,
       0,   956,   959,   957,   958,     0,     0,     0,  1094,   740,
    1094,  1094,  1094,     0,     0,     0,     0,     0,     0,     0,
       0,   941,   959,     0,   959,   942,   740,     0,   959,     0,
       0,     0,   943,   944,     0,     0,     0,     0,   945,   946,
       0,   948,     0,     0,   950,   951,   952,   953,   954,     0,
       0,   959,     0,   957,   959,     0,     0,     0,     0,     0,
       0,  1094,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1119,     0,     0,   941,     0,     0,
       0,   942,   599,  1094,  1094,     0,     0,  1094,   943,   944,
       0,     0,     0,  1913,   945,   946,   947,   948,     0,     0,
     950,   951,   952,   953,   954,   955,     0,   956,     0,   957,
     958,     0,   941,     0,  1931,     0,   942,   599,     0,     0,
       0,     0,     0,   943,   944,     0,     0,     0,  1094,   945,
     946,   947,   948,     0,     0,   950,   951,   952,   953,   954,
     955,     0,   956,     0,   957,   958,   941,     0,     0,     0,
     942,   599,     0,     0,     0,     0,     0,   943,   944,   959,
     959,     0,  1961,   945,   946,   947,   948,   959,     0,   950,
     951,   952,   953,   954,   955,     0,   956,     0,   957,   958,
       0,     0,   941,     0,  2098,     0,   942,   599,     0,     0,
       0,     0,     0,   943,   944,     0,     0,     0,   959,   945,
     946,   947,   948,     0,     0,   950,   951,   952,   953,   954,
     955,     0,   956,     0,   957,   958,     0,   959,     0,   941,
       0,  2113,   959,   942,   599,     0,     0,     0,     0,     0,
     943,   944,   959,   959,     0,     0,   945,   946,   947,   948,
       0,     0,   950,   951,   952,   953,   954,   955,     0,   956,
       0,   957,   958,     0,     0,     0,     0,     0,     0,     0,
     941,     0,     0,   959,   942,   599,     0,     0,     0,     0,
       0,   943,   944,   959,   959,     0,  2169,   945,   946,   947,
     948,     0,     0,   950,   951,   952,   953,   954,   955,     0,
     956,     0,   957,   958,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   959,     0,   959,     0,
       0,     0,     0,     0,     0,   941,     0,   959,     0,   942,
     599,     0,   959,     0,     0,   959,   943,   944,     0,     0,
       0,  2184,   945,   946,   947,   948,     0,   959,   950,   951,
     952,   953,   954,   955,     0,   956,   941,   957,   958,  2195,
     942,   599,     0,     0,     0,     0,     0,   943,   944,     0,
       0,     0,     0,   945,   946,   947,   948,     0,     0,   950,
     951,   952,   953,   954,   955,     0,   956,     0,   957,   958,
       0,     0,   941,     0,     0,     0,   942,   599,     0,     0,
       0,     0,     0,   943,   944,     0,     0,     0,  2199,   945,
     946,   947,   948,     0,   959,   950,   951,   952,   953,   954,
     955,     0,   956,     0,   957,   958,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   959,
       0,   959,     0,     0,     0,   959,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   959,   959,     0,
     959,     0,   941,     0,     0,     0,   942,   599,     0,     0,
     959,     0,   959,   943,   944,     0,     0,     0,  2258,   945,
     946,   947,   948,     0,     0,   950,   951,   952,   953,   954,
     955,     0,   956,     0,   957,   958,     0,     0,     0,     0,
       0,     0,     0,     0,   959,     0,   959,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   959,   959,
       0,   372,   373,   374,   375,     0,   377,     0,   378,     0,
     380,   381,     0,   382,     0,     0,     0,   384,     0,   386,
     387,     0,   959,   389,   390,   391,   959,   393,     0,   395,
     396,     0,     0,   403,     0,     0,   959,     0,   406,   407,
     408,   409,   410,   411,   412,   413,     0,   414,   415,     0,
       0,   420,   421,   422,     0,   424,     0,   426,     0,     0,
     429,   430,     0,     0,     0,     0,     0,     0,   437,   438,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   446,
       0,   448,     0,   449,   450,     0,     0,     0,   455,   456,
     457,     0,     0,   459,     0,     0,   461,   462,     0,   464,
     465,   466,     0,     0,     0,     0,   471,   472,     0,     0,
     474,     0,   476,   477,   478,     0,   480,   481,     0,     0,
     483,     0,   485,   486,   487,   488,   489,   490,     0,     0,
       0,     0,     0,     0,   498,   499,   500,     0,     0,     0,
       0,   505,   506,   507,     0,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,     0,   536,     0,   538,     0,   539,     0,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   941,     0,
       9,     0,   942,   599,     0,     0,     0,    10,     0,   943,
     944,     0,     0,     0,  2259,   945,   946,   947,   948,     0,
       0,   950,   951,   952,   953,   954,   955,     0,   956,     0,
     957,   958,     0,     0,     0,     0,     0,    11,    12,    13,
      14,     0,    15,    16,    17,    18,    19,    20,     0,   626,
      21,    22,   639,     0,   642,    23,    24,    25,     0,    26,
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
     197,     0,     0,     0,   198,   199,   200,   201,   202,   203,
     941,   204,   205,  2273,   942,   599,     0,     0,     0,     0,
       0,   943,   944,     0,     0,     0,     0,   945,   946,   947,
     948,     0,     0,   950,   951,   952,   953,   954,   955,     0,
     956,     0,   957,   958,     0,     0,   941,     0,     0,     0,
     942,   599,     0,     0,     0,     0,     0,   943,   944,     0,
       0,     0,  2280,   945,   946,   947,   948,   931,   932,   950,
     951,   952,   953,   954,   955,     0,   956,   941,   957,   958,
    2297,   942,   599,     0,     0,     0,     0,     0,   943,   944,
       0,     0,     0,     0,   945,   946,   947,   948,     0,     0,
     950,   951,   952,   953,   954,   955,     0,   956,   941,   957,
     958,  2357,   942,   599,     0,     0,     0,     0,     0,   943,
     944,     0,     0,     0,     0,   945,   946,   947,   948,     0,
       0,   950,   951,   952,   953,   954,   955,     0,   956,   941,
     957,   958,     0,   942,   599,     0,     0,     0,     0,     0,
     943,   944,     0,     0,     0,  2359,   945,   946,   947,   948,
       0,     0,   950,   951,   952,   953,   954,   955,     0,   956,
     941,   957,   958,     0,   942,   599,     0,     0,     0,     0,
       0,   943,   944,     0,     0,     0,  2371,   945,   946,   947,
     948,     0,     0,   950,   951,   952,   953,   954,   955,     0,
     956,   941,   957,   958,  2372,   942,   599,     0,     0,     0,
       0,     0,   943,   944,     0,     0,     0,     0,   945,   946,
     947,   948,     0,     0,   950,   951,   952,   953,   954,   955,
       0,   956,   941,   957,   958,  2374,   942,   599,     0,     0,
       0,     0,     0,   943,   944,     0,     0,     0,     0,   945,
     946,   947,   948,     0,     0,   950,   951,   952,   953,   954,
     955,     0,   956,   941,   957,   958,     0,   942,   599,     0,
       0,     0,     0,     0,   943,   944,     0,     0,     0,  2379,
     945,   946,   947,   948,     0,     0,   950,   951,   952,   953,
     954,   955,     0,   956,   941,   957,   958,     0,   942,   599,
       0,     0,     0,     0,     0,   943,   944,     0,     0,     0,
    2381,   945,   946,   947,   948,     0,     0,   950,   951,   952,
     953,   954,   955,     0,   956,   941,   957,   958,  2414,   942,
     599,     0,     0,     0,     0,     0,   943,   944,     0,     0,
       0,     0,   945,   946,   947,   948,     0,     0,   950,   951,
     952,   953,   954,   955,     0,   956,     0,   957,   958,   941,
       0,  2429,     0,   942,   599,     0,     0,     0,     0,     0,
     943,   944,     0,     0,     0,     0,   945,   946,   947,   948,
       0,     0,   950,   951,   952,   953,   954,   955,     0,   956,
     941,   957,   958,     0,   942,   599,     0,     0,     0,     0,
       0,   943,   944,     0,     0,     0,     0,   945,   946,   947,
     948,     0,     0,   950,   951,   952,   953,   954,   955,     0,
     956,     0,   957,   958
};

static const yytype_int16 yycheck[] =
{
      50,   387,   373,   480,   487,   488,   489,   490,   382,   622,
      62,    63,   370,   477,  1021,   396,   876,    69,   626,   742,
     254,  1439,   229,   230,   258,   406,   466,   408,   235,  1319,
     915,  1127,   413,   414,   415,  1017,   535,   648,   601,  1476,
     421,  1566,   461,   424,  1290,   426,    98,   868,   425,  1543,
     207,  1545,  1144,  1061,    76,   755,  1928,  1596,  1966,   735,
    1572,   637,  1290,  1572,  1472,   836,    63,  1508,   118,   437,
     428,   507,   122,     8,   836,  1583,   474,    99,  1540,  1508,
    1352,   647,   648,    15,   647,   648,   444,  1508,  1508,     8,
     383,   462,   175,  1856,   116,   971,  1508,  1508,   688,  1508,
     458,    20,    71,   383,    47,   463,   116,  1544,     8,   467,
    1592,   469,     5,  1638,   704,  1597,     7,     8,   665,    21,
     995,   182,   144,   182,   482,     0,     1,    15,     7,   129,
    1861,  1862,    15,     7,     7,    89,   494,    63,   496,     5,
       8,     8,    68,     5,     8,   503,   128,     5,  1156,     8,
     169,    15,   204,    20,    15,    16,    17,  1017,     5,    21,
       7,   191,  1169,   116,    90,    91,   166,    15,   122,     8,
     222,     8,     8,    15,   129,   157,   964,   965,   209,    37,
    1040,  1506,   965,  1508,    20,  1510,   129,  1512,    15,   629,
     254,    15,    58,   633,   258,    15,     3,   116,     8,    15,
     640,   155,     8,   639,    95,   129,   642,    21,   239,    37,
      20,    18,  1674,  1675,  1676,   791,   116,   401,   144,   129,
      86,  1506,  1506,  1508,  1508,  1510,  1510,   129,   154,     8,
     129,   185,   466,   124,   177,   217,   129,   116,   321,   208,
       8,    20,   116,   116,   834,  1535,   129,   257,   116,   116,
     149,   625,    20,   800,   315,   845,     8,   318,   288,   318,
     126,   149,   172,   282,   218,   129,   149,   129,   129,   299,
     129,   137,   862,   566,   200,   150,    64,   116,   755,   116,
     116,   129,   129,   576,   577,   578,   579,   129,   149,   116,
     474,  1506,    15,  1508,  2057,  1510,  1181,  1512,   252,   165,
     580,   129,   129,   684,   195,   129,   116,    41,   682,   129,
     116,   202,   902,   129,   246,   129,   368,   369,   716,   254,
      15,  1860,   374,   375,   376,   377,   916,   379,   380,  1425,
    2202,   383,   809,   385,   386,   387,   388,   116,   257,   391,
    2071,  2072,   394,  1615,   396,  1573,  1574,  1788,   116,   401,
     790,  1859,   404,   789,   406,   791,   408,   257,   966,  1788,
     412,   413,   414,   415,   116,   429,   743,  1788,  1788,   421,
    2137,   423,   424,   666,   426,  1857,  1788,  1788,   257,  1788,
     432,   433,   257,   257,   257,    15,   191,   439,   440,   257,
     257,   443,   258,   457,     8,   629,   689,  2164,   450,   633,
     464,   453,   466,   979,   802,   981,   640,  1083,  1284,  1180,
    1417,   779,   988,   465,  1004,   412,   468,  1179,   257,  1009,
     257,   257,   474,   475,   476,   477,    94,   479,   480,   995,
     257,  1438,   995,   483,   486,   487,   488,   489,   490,    15,
     492,    15,     8,   495,    15,   497,   498,   257,  1324,   501,
    1775,   257,   504,    23,   831,     8,   508,   169,     8,     8,
    1050,  2369,  1075,  1788,   671,  1473,   266,    37,  1168,  1794,
       8,  1563,  1564,  1798,     3,   209,     8,   282,   257,     5,
       8,     7,  1357,  1358,  1359,   537,  2358,   287,   538,   257,
    1775,  1775,   785,   912,   228,  1283,   208,    26,    16,    17,
     550,   551,   552,  1788,  1788,   257,    64,     8,   560,  1794,
    1794,   563,   564,   565,   566,     8,     8,    15,   568,   571,
     572,  1397,  1812,   575,   576,   577,   578,   579,    21,  2068,
    1967,   583,   584,     8,  2406,   557,   558,   830,  2050,   913,
     833,  2050,   982,   983,   984,   985,   986,   569,  1956,  2011,
     116,  2059,   257,   129,  1536,   129,   790,     8,   148,   129,
    1775,    92,   230,   116,     3,   629,   116,   116,   191,   633,
     282,   129,  1148,  1788,    92,   191,   640,    15,   116,  1794,
       8,   645,     8,  1798,   116,   208,   960,    26,   116,     5,
     180,   149,   208,     9,   751,   147,   148,   649,   650,   651,
     652,   653,   654,   655,     8,  1851,   658,   657,     3,    37,
    1856,    37,   147,   148,   666,   116,   284,     3,   149,    23,
       8,    37,    43,  1851,   116,   675,    21,   295,   180,    15,
    2092,   149,   684,    37,    84,   687,  2175,   689,     7,     5,
     847,   116,    23,     9,   851,   180,    67,    16,    17,   856,
      16,    17,   859,   860,     5,    21,    37,    23,  1032,   282,
     712,    82,   285,     3,    15,   116,    87,    88,  1042,     5,
     201,    37,     7,    94,  1264,    15,  1536,     5,     8,    15,
      15,     9,     8,   201,   128,   737,  1297,   739,    16,    17,
     742,   257,  1282,  1514,  1515,  1516,   191,  1518,  1519,   194,
    1423,  2163,   752,   755,   257,     8,     5,   257,   257,    37,
       9,    37,   764,   157,   921,   765,   923,    16,    17,   257,
       3,   773,   772,   775,    23,   257,   790,     8,   780,   257,
     782,  1297,    15,   785,  1297,  1611,  1299,     8,    37,  1439,
    1440,   191,  2267,  1618,  1619,  1620,   798,     8,   982,   983,
     984,   985,   986,  2452,  2453,     3,   257,   809,   208,  1418,
      21,  1420,     8,   815,     3,   257,  2465,    15,  1344,  1345,
    1346,  1347,  1348,     5,  1650,    21,    15,     9,   830,   314,
     315,   833,   257,   318,   319,     7,     8,   839,   838,  2226,
       3,  1357,  1358,  1359,  1357,  1358,  1359,     5,  2292,   191,
       7,     9,    15,   867,   868,    37,   257,   228,    16,    17,
       8,  2057,   876,     8,     8,   265,   208,     8,     8,   869,
       8,  1411,     8,    21,     8,     8,    21,  2289,     8,    37,
      21,    21,   282,    21,     8,   285,    12,    21,   259,   289,
     892,   893,    18,  1543,  2306,  1545,     8,    21,     8,   299,
       8,     8,    28,  2290,   304,    31,   908,     8,    34,    21,
       8,    21,     8,    21,    21,    41,    18,     8,     8,    45,
    2288,     8,   894,    49,    26,    21,     8,    15,   930,  1256,
      21,   931,   303,  2173,    21,  2416,     8,   909,    15,    21,
     282,    67,     8,   285,     8,    71,    72,  2428,   290,    21,
       8,    77,    78,     8,     8,    21,   298,    83,    84,     8,
      86,    87,    88,    89,  1896,    91,    21,    21,   982,   983,
     984,   985,   986,     8,   100,     8,   990,   991,     8,   105,
    2367,   107,    22,     8,    24,   111,    21,     8,    21,   115,
      15,   117,     8,    33,     8,    35,  2364,     8,   124,  1834,
      21,     8,   128,  1017,     8,    21,   132,  1331,   134,     8,
      21,  1013,  1333,  1337,  1014,   141,   142,  1019,     8,   145,
     146,     8,    21,  1025,  1697,   151,  1040,   153,   254,     8,
       8,   157,   258,  1190,    21,     8,  1038,     8,     7,  1196,
       8,  2087,    21,  1200,  1287,  1202,  1203,  1204,    21,  1206,
      21,  1208,  1610,    21,  1880,     8,  1377,    15,   184,     8,
     186,  1063,     8,  1406,  1078,  1408,  1068,     8,    21,  1390,
    1896,     8,    21,  1723,   149,    21,  1902,     8,  1904,  1403,
      21,     8,  1084,     8,    21,  1416,  1896,  1627,     8,   129,
      21,  1091,  1902,     3,    21,   249,    21,  1099,     8,     7,
       8,    21,  1618,  1619,  1620,  1618,  1619,  1620,  1846,  1847,
    1848,  1849,  1850,  1846,  1847,  1848,  1849,  1850,   158,   159,
       3,   161,   162,     8,     8,     8,     5,    15,    16,    17,
     149,    22,     7,    24,  1134,    15,    21,    16,    17,    27,
    1448,    15,    33,    22,    35,    24,    16,    17,    36,  1689,
       5,    21,   192,     5,    33,    10,    35,     9,    37,    14,
      15,    16,    17,    15,    16,    17,    15,     8,    15,     8,
       8,    15,    27,     8,     8,    27,    64,    37,  1178,    34,
      21,    36,    21,    21,    36,     8,    21,  1495,   849,   850,
      41,   852,     8,     8,   234,     8,    15,   256,    21,   258,
     259,    15,    16,    17,    92,    21,    21,   247,    21,    64,
    1534,    15,    64,    27,     8,   336,     8,     8,   339,   340,
      71,  1221,    36,     8,  1614,     8,     8,    21,  2274,    21,
      21,  1231,  1232,  1233,  1391,    15,    21,    92,    21,    21,
      92,   129,    15,  1243,     8,    59,    15,     8,  1248,     8,
      64,     8,     8,  1253,     7,  1257,  1258,    21,   124,    84,
      21,   149,    21,  2220,    21,    21,    15,   158,   159,     8,
     161,   162,    15,   399,   129,     7,     8,   129,    92,  1281,
     159,  1605,    21,   162,   135,  1287,     8,     8,  1737,  1291,
    1739,  1740,   446,     8,   149,    15,     8,   149,    15,    21,
      21,   192,  1751,     8,    15,  1629,    21,     8,  1465,    21,
       8,   166,  1761,   201,  1763,  1878,    21,  1641,   169,     8,
      21,  1645,    15,    21,   316,   317,     8,   481,     8,  1660,
      16,    17,    21,   239,     8,   149,    15,   491,  1352,    21,
     191,    21,     8,   234,  2170,    15,   201,    21,     8,   201,
       8,     8,     8,    15,     8,    21,   247,   208,   209,  1885,
    1362,    21,    15,    21,    21,    21,   191,    21,   247,  2195,
     221,     8,   223,   224,    15,   226,   502,    15,   229,  2073,
    2074,  2075,    15,   208,    21,  1573,  1574,   201,    15,   543,
     544,   545,   546,   547,  1618,  1619,  1620,   245,   246,   990,
     991,  1547,  1548,  1405,  1406,    15,  1408,  2448,  2449,  2344,
    2345,   857,   858,    15,  1416,    15,  1418,    15,  1420,    15,
     124,  1423,    15,     3,     5,   246,   305,   306,   307,    10,
    1614,   282,    15,    14,    15,    16,    17,   246,    26,    21,
     265,  1455,     8,     7,    15,  2402,    27,   601,   602,   603,
     240,   605,  1454,    34,    15,    36,    15,   282,   612,     8,
     285,  1463,    15,     8,   289,   290,   175,  1469,    15,   320,
       8,  1471,   626,   298,   299,    15,   149,  1479,    15,   304,
       8,     8,    15,    64,  1498,     8,     8,    26,     7,    15,
    1490,    15,  1492,    62,  1496,    15,     8,     8,   287,    15,
    1514,  1515,  1516,    21,  1518,  1519,     8,     8,  1522,     8,
     213,    92,    15,     8,   668,     9,    64,  1517,   129,     9,
       8,    21,  1536,     8,     8,    67,  1540,     8,  1528,   683,
      37,    18,     5,    15,    44,    15,     9,    15,    15,    15,
      15,  1541,    15,    16,    17,    15,    15,     8,   129,     7,
     129,  1553,    26,    15,    27,     7,    21,   711,  1558,    26,
    1560,    21,    21,    36,   718,    37,     7,    15,   149,     7,
     724,   725,  2222,     8,     8,    15,  1897,    87,    15,    26,
       8,  1583,    21,    93,    15,   166,    15,     8,    21,    15,
     402,    64,  1900,    15,  1596,    15,    15,    21,  2161,    15,
    1614,  1615,    15,    21,    15,    15,    15,    15,    15,   119,
      15,     5,     5,  1615,    15,   769,  1618,  1619,  1620,    92,
     201,    21,    15,    16,    17,    15,  1628,     8,     7,    15,
      62,  1967,     8,   143,    27,   145,     8,     8,  2288,     8,
      15,  2291,  2292,    36,     7,   166,   255,    15,   239,    16,
      15,    21,   208,    15,    15,    21,   129,     8,  1660,     7,
    1674,  1675,  1676,    15,   328,   315,   329,     7,   178,    15,
     246,    64,   246,   183,   246,     5,   149,   187,  1680,   246,
       8,   191,    15,   246,   194,    21,    15,    21,   842,   843,
       8,  2341,     7,   166,    21,  1697,    21,    21,     8,    92,
      26,   513,    15,   515,     8,    21,   216,   173,    15,    15,
     522,   523,   524,  2363,  2364,     8,   528,   529,   530,   531,
     230,   533,   534,  2137,  2048,   255,   236,     5,   201,  1731,
    1732,     9,     7,    21,  2058,    15,   129,     5,    16,    17,
     208,     9,    15,    21,    18,    23,    63,     8,    16,    17,
      71,    68,    15,    15,  1756,    23,   149,    25,  2408,    37,
      28,    29,    30,    31,    32,    15,    15,    15,    21,    37,
      21,     5,    15,    90,    91,    21,    21,    21,    15,  2212,
    2213,    21,    21,    21,   910,     8,    15,   941,   942,   943,
     944,   945,   946,   947,   948,   949,   950,   951,   952,   953,
     954,   955,   956,   957,   958,   959,    15,   124,   201,     7,
       9,    21,   966,    20,    26,    45,    46,   971,    48,    49,
      21,    21,    26,    53,   978,    21,   980,   144,    21,    15,
      21,    61,    15,     5,    26,     7,    66,   154,    10,    69,
      18,   995,    14,    15,    16,    17,     8,    77,    21,    79,
      15,    81,    15,     7,    21,    27,    15,  1859,  1860,  1861,
    1862,  2288,    34,  2290,    36,    26,     8,  1021,    15,   254,
    1872,  2192,    21,  1027,   104,     5,    21,    15,   132,     9,
       8,     7,  1896,   200,  1010,   115,    16,    17,  1902,  1043,
      21,     7,    64,    23,    21,    25,    37,  1899,    28,    29,
      30,    31,    32,    21,     7,     7,    21,    37,    21,   139,
     255,    15,     7,    21,    15,  1915,   233,    15,    15,     5,
      92,    15,   152,     9,    10,    15,    15,   244,    14,    15,
      16,    17,    15,    15,    15,     8,  1936,     8,     7,     7,
     170,    27,    21,     8,    21,    15,   176,     7,    34,  1951,
      36,     7,    15,  1955,   184,  1957,   186,   129,   188,    21,
     190,    78,     8,   327,     7,  1967,     7,   197,    21,    17,
      15,  1973,  1974,  1127,    21,    15,     8,   149,    64,    17,
    1980,    15,     7,     7,   214,   215,    15,     7,     5,  1989,
     893,   803,  1146,   128,   220,  1258,   901,  2011,    15,    16,
      17,  1953,   232,  1831,  1558,  1182,    92,  2007,  1087,   239,
      27,  1562,   574,  1832,  2170,  1169,  1170,  1171,   702,    36,
     585,  1289,     5,   253,     7,   582,   256,    10,   930,   201,
    2030,    14,    15,    16,    17,  1592,  2175,   930,  2070,  1859,
    2050,  1851,  1479,   129,    27,  1151,  1698,    64,  2119,  1951,
    1463,    34,  2139,    36,  1974,  1043,  1023,  2059,  1379,  1400,
      63,  1085,  1671,   149,    75,    68,  2068,  1673,  2070,  2071,
    2072,  2073,  2074,  2075,  1880,    92,  2454,   457,  2092,   703,
    1234,    64,  1386,  1423,   244,  1032,   244,    90,    91,  1902,
       5,   244,   244,   783,     9,    45,    46,  1611,    48,    49,
    2100,    16,    17,    53,  1614,   995,    21,  1068,    23,    92,
    1099,    61,   129,   649,  1171,   201,    66,   651,   653,    69,
     652,   829,    37,   654,  2221,  1402,  2099,    77,  2406,    79,
    1284,    81,   149,  1404,  1955,  2137,  2138,  2139,  2274,  1265,
    1013,   144,  1296,   798,  1011,  2382,   129,  1899,  2162,  2163,
       5,   154,  1084,  1025,   104,    10,  1038,  1460,  2325,    14,
      15,    16,    17,  1938,  2287,   115,   149,  2408,  2430,  2450,
    1324,  2229,    27,  2175,  1723,  2452,  1958,  1477,   498,    34,
    1440,    36,  1336,     5,   201,    40,   410,   658,    10,   139,
     377,  1904,    14,    15,    16,    17,  1528,   200,   753,  1962,
    1775,  2202,   152,  1750,  1794,    27,  1798,  1755,  1987,    64,
    2212,  2213,    34,  1986,    36,  2253,  1788,  2007,   201,  2221,
     170,  1221,  1248,  1243,  1253,    -1,   176,    -1,   231,    -1,
      -1,  1385,  1386,    -1,   184,    -1,   186,    92,   188,  1051,
     190,   244,    64,    -1,    -1,    -1,  1400,   197,    -1,    -1,
    1062,    -1,    -1,  1407,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1417,   214,   215,    -1,    -1,    -1,  1423,
      92,  1425,    -1,    -1,   129,  2289,  2278,    -1,    -1,    -1,
      -1,    -1,   232,    -1,  1438,    -1,  2288,    -1,  2290,   429,
      -1,    -1,  2306,    -1,   149,    -1,    -1,  1451,    -1,  2313,
      -1,    -1,  2302,   253,    -1,    -1,   256,   129,  1462,    -1,
      -1,  2311,  2314,    -1,    -1,    -1,    -1,   457,    -1,    -1,
      -1,  1475,    -1,    -1,   464,     5,  1480,   149,  1482,    -1,
      10,    -1,   472,    -1,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,  1155,  2344,  2345,   201,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,     5,
      -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,  1189,    -1,   201,
    2382,    27,  2384,  1195,    64,    -1,    -1,  1199,    34,  1201,
      36,    -1,    -1,  1205,    -1,  1207,    -1,     7,    -1,    -1,
      10,    -1,    -1,    -1,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    92,    -1,  1568,    -1,    -1,    27,    64,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      -1,    -1,  2432,    -1,    -1,    -1,    -1,  2437,    -1,    -1,
      -1,   581,    -1,    -1,    -1,    -1,    92,    -1,    -1,   129,
    2450,    -1,  2452,  2453,    64,  1609,  1610,  1611,    -1,    -1,
      -1,    -1,    -1,     5,    -1,  2465,    -1,    -1,    10,   149,
      -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    92,   129,    -1,    27,  1640,    -1,    -1,  1643,
      -1,    -1,    34,    -1,    36,    -1,    -1,  1651,    -1,    -1,
      -1,    -1,    -1,   149,    -1,   645,    -1,    -1,     7,    -1,
      -1,    10,    -1,    -1,    -1,    14,    15,    16,    17,   129,
      -1,   201,    64,    -1,    -1,    -1,    -1,    -1,    27,  1683,
      -1,  1685,    -1,    -1,    -1,    34,    -1,    36,    -1,   149,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    -1,     7,   201,   166,    10,    -1,    -1,
      -1,    14,    15,    16,    17,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    78,
      -1,    34,    -1,    36,    -1,    -1,    -1,   129,    -1,    -1,
      -1,   201,    -1,    92,    -1,    -1,     7,   737,    -1,    10,
      -1,  1413,    -1,    14,    15,    16,    17,   149,    -1,    -1,
      -1,    64,    -1,    -1,    -1,   755,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    36,    -1,    -1,   768,    -1,
     129,    -1,    -1,    -1,    -1,    -1,   776,   777,    -1,    92,
      -1,   781,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1461,
     149,    -1,    -1,    64,    -1,    -1,    -1,    -1,     7,   201,
      -1,    10,    -1,    -1,    -1,    14,    15,    16,    17,   809,
      -1,  1825,  1826,    -1,    -1,    -1,   129,   817,    27,  1833,
      -1,    92,    -1,    -1,    -1,    34,    -1,    36,    -1,  1501,
      -1,    -1,  1504,    -1,    -1,  1507,   149,  1509,    -1,  1511,
      -1,  1513,   201,    -1,     7,    -1,   846,    10,   848,    -1,
      44,    14,    15,    16,    17,    64,    -1,    -1,   129,    -1,
    1874,    -1,    -1,    -1,    27,    -1,  1880,   867,   868,    -1,
      -1,    34,    -1,    36,    -1,    -1,   876,   877,   149,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,   201,    -1,
      -1,  1905,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,
    1914,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1931,  1932,    -1,
     129,    -1,    -1,    -1,    -1,   119,    -1,    -1,     7,    92,
     201,    10,    -1,    -1,    -1,    14,    15,    16,    17,    -1,
     149,    -1,    -1,    -1,  1958,    -1,    -1,    -1,    27,   143,
      -1,   145,  1966,    -1,    -1,    34,    -1,    36,    -1,    -1,
      -1,  1975,    -1,    -1,   964,   965,   129,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1991,    -1,  1993,
      -1,    -1,    -1,    -1,   178,    64,   149,    -1,    -1,   183,
     990,   991,   201,   187,    -1,    -1,     7,   191,    -1,    10,
     194,    -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    92,   613,    -1,    27,  1017,    -1,    -1,
      -1,    -1,   216,    34,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   230,    -1,   201,    -1,
    1040,    10,   236,    -1,    -1,    14,    15,    16,    17,    -1,
     129,    -1,    -1,    64,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    36,  2082,    -1,
     149,    -1,    -1,  2087,    -1,  1747,    -1,    -1,  1078,    -1,
    1752,    92,    -1,    -1,  2098,  2099,    -1,    -1,    -1,  2103,
      -1,    -1,    -1,  1765,    -1,    64,    -1,    -1,    -1,  2113,
      -1,    -1,    -1,    10,  2118,    -1,    -1,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,  1787,    -1,    -1,   129,    -1,
      27,  1793,   201,    92,    -1,  1797,    -1,    34,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2170,    64,    -1,    -1,
     129,    -1,    -1,   762,    -1,    -1,    -1,   766,  1168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,     7,
     149,     9,    10,    -1,    -1,    92,    -1,    -1,    16,    17,
     201,  2205,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,  2220,    35,    -1,    37,
      38,    -1,    -1,     5,   813,    -1,    -1,     9,    -1,    -1,
      -1,    -1,   129,    -1,    16,    17,   825,    -1,    -1,    -1,
      22,    23,   201,    25,    -1,    -1,    28,    29,    30,    31,
      32,    -1,   149,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2273,
    2274,    -1,    -1,  2277,    -1,  2279,    -1,    -1,    -1,    -1,
      -1,   870,   871,   872,   873,    -1,   875,    -1,    -1,    -1,
      -1,  2295,  2296,  2297,    -1,    -1,    -1,    -1,  1288,    -1,
      -1,    -1,  1964,  2307,   201,    -1,    -1,    -1,    -1,  2313,
      -1,    -1,    -1,    -1,    -1,  1977,    -1,    -1,    -1,    -1,
    1982,  2325,    -1,  1985,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1995,    -1,  1997,    -1,  1999,    -1,  2001,
      -1,    -1,    -1,    -1,    -1,    -1,   935,    -1,   937,   938,
     939,   940,    -1,  2357,  2358,     5,    -1,    -1,    -1,     9,
      10,    -1,  1352,    -1,    -1,  2369,    16,    17,  2372,    -1,
    2374,    -1,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2402,    -1,
      -1,    -1,  2406,    -1,    -1,    -1,  2410,   996,    -1,    -1,
    2414,    -1,  2416,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2428,  2429,  2430,    -1,  1418,  1018,
    1420,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1028,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1439,
    1440,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1449,
    1049,    -1,    -1,    -1,    -1,  1455,    -1,  1457,    -1,    -1,
    1460,    -1,    -1,     5,    -1,    -1,  1065,     9,    10,    -1,
    1069,  1070,  1472,    -1,    16,    17,  1476,  1477,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    38,    -1,  1498,    -1,
      -1,    -1,    -1,    -1,    -1,  1505,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1514,  1515,  1516,    -1,  1518,  1519,
      -1,    -1,  1522,    -1,    -1,    -1,    -1,  1126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1536,    -1,  1538,    -1,
    1540,    -1,    -1,  1543,  1544,  1545,    -1,  1547,  1548,     5,
      -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,  1583,    -1,    -1,  1185,  1186,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,  2286,  1615,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
       5,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,  1674,  1675,  1676,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1300,  1301,  1302,  1303,  1304,  1305,  1306,  1307,  1308,
    1309,  1310,  1311,  1312,  1313,  1314,  1315,  1316,  1317,  1318,
      -1,    -1,    -1,  1723,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1334,    -1,    -1,    -1,    -1,
      -1,     5,  1341,    -1,  1343,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,  1353,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,  1384,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,     5,    -1,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,  1846,  1847,  1848,  1849,
    1850,    -1,     5,  1452,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,  1466,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,     5,  1487,    -1,
      -1,     9,    10,    -1,    -1,    -1,  1896,    -1,    16,    17,
      -1,    -1,  1902,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,  1533,  1935,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,  1956,    -1,     5,    -1,
      -1,    -1,     9,    10,    -1,    -1,    -1,  1967,  1567,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,  1987,    35,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1600,    -1,    -1,    -1,    -1,    -1,    -1,  1607,    -1,
      -1,  2011,  2012,    -1,  1613,     5,    -1,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,  1636,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,  1648,
      -1,    -1,    -1,    -1,     5,    -1,    -1,  1656,     9,  2059,
      -1,    -1,    -1,    -1,    -1,    16,    17,  1666,    -1,    -1,
    1669,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,  1684,    37,    38,    -1,  2089,
      -1,    -1,  2092,    -1,  2094,    -1,  1695,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,
    1709,    -1,    16,    17,    -1,    -1,  1715,    21,    22,    23,
      24,    25,  1721,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,  2162,  2163,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
       9,    10,  2222,    -1,    -1,    -1,  2226,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,  1837,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,  1881,    37,    38,    -1,    -1,    -1,  2288,  2289,
    2290,  2291,  2292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,  1901,    -1,  1903,     9,  2306,    -1,  1907,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
      -1,    25,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      -1,  1930,    -1,    37,  1933,    -1,    -1,    -1,    -1,    -1,
      -1,  2341,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1953,    -1,    -1,     5,    -1,    -1,
      -1,     9,    10,  2363,  2364,    -1,    -1,  2367,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,  2408,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,     5,    -1,    -1,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,  2038,
    2039,    -1,    21,    22,    23,    24,    25,  2046,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,  2077,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,  2096,    -1,     5,
      -1,     7,  2101,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,  2111,  2112,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    -1,    -1,  2142,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,  2152,  2153,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2185,    -1,  2187,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,  2196,    -1,     9,
      10,    -1,  2201,    -1,    -1,  2204,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,  2216,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,  2283,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2318,
      -1,  2320,    -1,    -1,    -1,  2324,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2336,  2337,    -1,
    2339,    -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,
    2349,    -1,  2351,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2383,    -1,  2385,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2397,  2398,
      -1,    14,    15,    16,    17,    -1,    19,    -1,    21,    -1,
      23,    24,    -1,    26,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,  2421,    36,    37,    38,  2425,    40,    -1,    42,
      43,    -1,    -1,    46,    -1,    -1,  2435,    -1,    51,    52,
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
     193,   194,   195,   196,   197,   198,   199,   200,     5,    -1,
       6,    -1,     9,    10,    -1,    -1,    -1,    13,    -1,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    -1,   252,
      56,    57,   255,    -1,   257,    61,    62,    63,    -1,    65,
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
     326,    -1,    -1,    -1,   330,   331,   332,   333,   334,   335,
       5,   337,   338,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,     5,    -1,    -1,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,   590,   591,    28,
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
      -1,    35,     5,    37,    38,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,     5,    37,    38,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,     5,
      -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   344,     0,     1,   150,   257,   345,   346,   116,     6,
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
     332,   333,   334,   335,   337,   338,   347,   349,   352,   364,
     365,   369,   370,   371,   377,   378,   379,   380,   382,   383,
     385,   387,   388,   389,   390,   397,   398,   399,   400,   401,
     402,   406,   407,   408,   412,   413,   451,   453,   466,   509,
     510,   512,   513,   519,   520,   521,   522,   529,   530,   531,
     532,   534,   537,   541,   542,   543,   544,   545,   551,   552,
     553,   564,   565,   566,   568,   571,   574,   579,   580,   582,
     584,   586,   589,   590,   614,   615,   626,   627,   628,   629,
     634,   637,   640,   643,   644,   692,   693,   694,   695,   696,
     697,   698,   699,   705,   707,   709,   711,   713,   714,   715,
     716,   717,   720,   722,   723,   724,   727,   728,   732,   733,
     735,   736,   737,   738,   739,   740,   741,   744,   749,   754,
     756,   757,   758,   759,   761,   763,   764,   765,   766,   767,
     784,   787,   788,   789,   790,   796,   799,   804,   805,   806,
     809,   810,   811,   812,   813,   814,   815,   816,   817,   818,
     819,   820,   821,   822,   823,   828,   829,   830,   831,   832,
     842,   843,   844,   845,   846,   847,   848,   849,    15,   476,
     476,   538,   538,   538,   538,   538,   476,   538,   538,   348,
     538,   538,   538,   476,   538,   476,   538,   538,   476,   538,
     538,   538,   475,   538,   476,   538,   538,     7,    15,   477,
      15,   476,   597,   538,   476,   361,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   129,   354,   518,   518,
     538,   538,   538,   476,   538,   354,   538,   476,   476,   538,
     538,   475,   348,   476,   476,    64,   360,   538,   538,   476,
     476,   476,   476,   476,   476,   476,   538,   415,   538,   538,
     538,   354,   452,   348,   476,   538,   538,   538,   476,   538,
     476,   538,   538,   476,   538,   538,   538,   476,   348,   476,
     361,   538,   538,   361,   538,   476,   538,   538,   538,   476,
     538,   538,   476,   538,   476,   538,   538,   538,   538,   538,
     538,    15,   476,   575,   476,   348,   476,   476,   538,   538,
     538,    15,     8,   476,   476,   538,   538,   538,   476,   538,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   476,   538,   476,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   538,
      15,    15,    15,   354,   861,   257,   563,   124,   233,   385,
      15,   357,   563,     8,     8,     8,     8,     7,     8,   124,
     349,   372,     8,   354,   386,     8,     8,     8,     8,     8,
     533,     8,   533,     8,     8,     8,     8,   533,   563,     7,
     218,   252,   510,   512,   521,   522,   239,   530,   530,    10,
      14,    15,    16,    17,    27,    34,    36,    64,    92,   149,
     201,   354,   366,   482,   483,   485,   486,   487,   488,   494,
     495,   496,   497,   498,   501,    15,   538,     5,     9,    15,
      16,    17,   129,   484,   486,   494,   547,   561,   562,   538,
      15,   547,   538,     5,   546,   547,   562,   547,     8,     8,
       8,     8,     8,     8,     8,     8,     7,     8,     8,     5,
       7,   354,   624,   625,   354,   617,   477,    15,    15,   149,
     465,   354,   354,   725,   726,     8,   354,   641,   642,   726,
     354,   356,   354,    15,   514,   559,    23,    37,   354,   404,
     405,    15,   354,   587,   354,   656,   656,   354,   638,   639,
     354,   517,   414,    15,   354,   567,   149,   731,   517,     7,
     460,   461,   476,   598,   599,   354,   593,   599,    15,   539,
     354,   569,   570,   517,    15,    15,   517,   731,   518,   517,
     517,   517,   517,   354,   517,   357,   517,    15,   409,   477,
     485,   486,    15,   351,   354,   354,   635,   636,   467,   468,
     469,   470,     8,   657,   721,    15,   354,   581,   354,   572,
     573,    15,    15,   354,   477,    15,   482,   734,    15,    15,
     354,   708,   710,     8,   354,    37,   403,    15,   486,   487,
     477,    15,    15,   539,   465,   477,   486,   354,   700,     5,
      15,   561,   562,   477,   354,   355,   477,   560,    15,   485,
     618,   619,   593,   597,   354,   585,   354,   680,   680,    15,
     354,   583,   700,   482,   493,   477,   361,    15,   354,   686,
     686,   686,   686,   686,     7,   482,   576,   577,   354,   578,
     477,   350,   354,   477,   354,   706,   708,   354,   476,   477,
     354,   454,    15,    15,   560,   354,    15,   599,    15,   599,
     599,   599,   599,   770,   826,   599,   599,   599,   599,   599,
     599,   770,   354,   361,   833,   834,   835,    15,    15,    15,
     482,   482,   482,   482,   481,   482,    15,    15,   361,   850,
     851,   852,   853,   361,   854,   855,   856,   857,   858,   361,
     859,   860,   348,   348,   124,     5,    21,   354,   358,   359,
     353,   361,   354,   354,   354,   405,     7,   361,   348,   124,
     354,   354,     5,    15,   392,   393,   354,   405,   405,   405,
     405,   404,   485,   403,   354,   354,   409,   416,   417,   419,
     420,   538,   538,   239,   395,   482,   483,   482,   482,   482,
     482,     5,     9,    16,    17,    22,    23,    24,    25,    26,
      28,    29,    30,    31,    32,    33,    35,    37,    38,   366,
      15,   246,     3,    15,   246,   246,    15,   491,   492,    21,
     535,   559,   493,     5,     9,   166,   548,   549,   550,   561,
      26,   561,     5,     9,    23,    37,   484,   560,   561,   560,
       8,    15,   486,   554,   555,    15,   482,   483,   498,   556,
     557,   558,   556,   567,   354,   581,   583,   585,   587,   354,
       7,   361,   706,     8,    21,   619,   405,   507,   482,   240,
     533,    15,   361,    15,   459,     8,   559,     7,   482,   515,
     516,   517,    15,   354,   459,   405,   464,   465,     8,   416,
     507,   459,    15,     8,    21,     5,     7,   462,   463,   482,
     354,     8,    21,     5,    58,    86,   126,   137,   165,   258,
     600,   596,   597,   175,   588,   482,   149,   528,     8,   482,
     482,   353,   354,   410,   411,   485,   490,   354,    26,   354,
     523,   524,   526,   357,     8,     8,    15,   231,   385,   471,
     361,     8,   721,   354,   485,   690,   700,   718,   719,     8,
      26,     5,     9,    16,    17,    22,    23,    24,    25,    28,
      29,    30,    31,    32,    33,    34,    35,    37,    38,   366,
     367,   368,   354,   361,   375,   485,   482,    15,   361,   354,
     354,   485,   485,   508,     8,   657,   712,   354,   485,   645,
     646,   354,   449,   450,   528,   405,    18,   560,   561,   560,
     381,   384,   624,   619,     7,   597,   599,   690,   700,   701,
     702,   404,   405,   443,   444,    62,   485,   745,    15,    15,
       7,     8,    21,   575,   405,   357,   405,   459,     8,   655,
     677,    21,   361,   354,     8,   482,   482,   459,   485,   533,
     791,   485,   287,   803,   803,   533,   800,   803,    15,   533,
     768,   533,   807,   768,   768,   533,   785,   533,   797,   459,
     147,   148,   180,   314,   315,   318,   319,   362,   836,   837,
     838,     8,    21,   486,   661,   839,    21,   839,   361,   742,
     743,     8,     8,     8,     8,   485,   488,   489,   760,   485,
     762,   191,   208,     8,    21,    41,   209,   228,     8,    21,
     336,   339,   340,     8,    21,   354,   350,   348,     8,    21,
     213,   362,   459,    44,    87,    93,   119,   143,   145,   178,
     183,   187,   191,   194,   216,   230,   236,   373,   374,   376,
     354,   348,   476,   539,   559,   386,   459,   533,   533,     8,
      37,    15,   354,   422,   427,   361,    15,   502,    21,     8,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   559,
      64,   129,   478,   480,   559,   485,   496,   499,    64,   499,
     493,     8,    21,     5,   482,   536,   550,     8,    21,     5,
       9,   482,    21,   482,   561,   561,   561,   561,   561,    21,
     554,   554,     8,   482,   483,   557,   558,     8,     8,     8,
     459,   459,   476,    43,    67,    82,    87,    88,    94,   228,
     259,   303,   628,   625,   361,   489,   505,    21,   354,    15,
     481,    67,   460,   642,   482,     7,     8,    21,   535,    37,
       8,    21,   639,   485,   488,   504,   506,   559,   729,   462,
       7,   459,   599,    15,    15,    15,    15,    15,    15,   588,
     599,   354,    21,   540,   570,    21,    21,    15,     8,    21,
       8,   492,   486,     8,   525,    26,   353,   636,   468,   129,
     472,   473,   474,   390,   169,   208,   282,   361,    15,     7,
       8,    21,   573,    21,    21,   147,   148,   180,    21,    18,
      21,     7,   482,   500,   175,   321,    37,     8,    21,   361,
       8,    21,    26,     8,    21,   540,   482,    21,   445,   446,
     445,    21,     7,   599,   588,    15,     7,     8,    21,     8,
      15,    15,    26,   687,   688,   690,   481,   482,   577,   361,
       8,   677,     8,   655,   386,   376,   363,    21,    21,    21,
     599,   533,    21,   599,   533,   827,   599,   533,   599,   533,
     599,   533,   599,   533,    15,    15,    15,    15,    15,    15,
     361,   835,     8,    21,    21,   182,   315,   318,     8,    21,
     361,   361,   361,   482,    15,    15,     8,    21,     8,    21,
      15,    15,   851,    15,    15,    15,   855,    15,    15,   860,
     357,   354,   359,    15,   391,   392,   459,   476,    15,     7,
       8,   354,   459,    15,   496,     5,   394,   482,   550,   405,
     485,   419,    15,    16,    17,    27,    36,    59,    64,    92,
     149,   201,   418,   420,   430,   431,   432,   433,   434,   435,
     436,   437,   422,   427,   428,   429,    15,   423,   424,    62,
     482,   556,   483,   478,    21,     8,   479,   482,   500,   550,
       7,   559,   465,   482,   559,     8,   555,    21,     8,     8,
       8,   483,   558,   483,   558,   483,   558,   354,   255,     8,
      21,   465,   464,    21,     7,    21,   482,   515,    21,   465,
     533,     8,    21,   550,   730,     8,    21,   463,   482,   600,
     559,    15,   602,   354,   601,   601,   482,   601,   459,   599,
     239,   517,   481,   411,   411,   354,   482,   524,    21,   482,
     500,     8,    21,    16,    15,    15,    15,   481,   718,   719,
     477,   485,   750,     7,   482,     7,    21,    21,   354,   595,
     486,   485,   646,   599,   647,   482,   450,   533,     8,    47,
     177,   354,   448,   361,   616,   618,   588,     7,     7,   482,
     703,   704,   701,   702,   444,   482,     5,   602,   746,   747,
     753,   482,   612,     8,    21,    15,    21,    71,   208,   361,
     361,   477,   172,   354,   457,   458,   486,   191,   208,   282,
     285,   290,   298,   771,   772,   773,   780,   792,   793,   794,
     599,   266,   801,   802,   803,   599,    37,   485,   824,   825,
      84,   265,   289,   299,   304,   769,   771,   772,   773,   774,
     775,   776,   778,   779,   780,   599,   771,   772,   773,   774,
     775,   776,   778,   779,   780,   793,   794,   808,   599,   771,
     772,   773,   780,   786,   599,   771,   772,   798,   599,   839,
     839,   839,   361,   840,   841,   839,   839,   486,   743,   328,
     315,   329,   559,   478,   489,   485,   661,   361,   681,   687,
     701,   687,   645,   645,   354,    18,    26,   396,    15,   375,
       7,   361,   391,   540,   540,   395,     5,   482,   433,   434,
     435,   438,   434,   436,   434,   436,   246,   246,   246,   246,
     246,     8,    37,   354,   421,   485,     5,   423,   424,     8,
      15,    16,    17,   149,   354,   421,   425,   426,   439,   440,
     441,   442,    15,   424,    15,    21,   503,    21,    21,   492,
     559,   482,   493,   536,   549,   561,   526,   527,   483,   527,
     527,   527,   459,   354,   620,   623,   559,     8,    21,     7,
     395,   482,   559,   482,   559,   550,   613,   482,   603,   604,
      21,    21,    21,    21,     8,     8,   254,   511,   517,    21,
     473,   474,   661,   661,   661,    21,    21,   354,    15,    21,
     482,     7,     7,   482,   459,   173,     8,   651,   652,   653,
     654,   655,   657,   658,   659,   662,   663,   664,   677,   685,
     526,   446,    15,    15,   447,   255,     8,     7,     8,    21,
      21,    21,     8,    21,    21,   688,   689,    15,    15,   354,
     354,   455,   456,    18,     8,    26,   770,    15,   770,   770,
      15,   599,   792,   770,   599,   801,   354,     8,    21,    15,
     770,    15,   770,    15,   599,   769,   599,   808,   599,   786,
     599,   798,    21,    21,    21,   316,   317,     8,    21,    21,
      21,    15,    15,   478,    21,    21,    22,    24,    33,    35,
     158,   159,   161,   162,   192,   234,   247,   682,   683,   684,
       8,    21,    21,    21,    21,    21,    21,    21,   482,   482,
     630,   631,    21,   374,   396,     5,   482,   386,     8,    21,
       8,   499,   499,   499,   499,   499,   430,     5,    15,   420,
     431,   424,   354,   421,   429,   439,   440,   440,     8,    21,
       7,    16,    17,     5,    37,     9,   439,   482,    20,   492,
     479,    21,    26,    21,    21,    21,    21,    15,   489,   550,
     465,   641,   477,   504,   550,   730,   482,    21,     7,     8,
      21,   482,   361,    15,    21,    21,    21,     7,   751,   752,
     753,   482,   482,     7,   485,   648,   361,   653,    26,   448,
      26,   367,   620,   618,   354,   591,   592,   593,   594,   704,
     747,   599,    78,   576,   354,   656,   701,   678,    18,     8,
     354,   458,   482,   599,   781,   361,   599,   599,   826,   485,
     824,   361,   482,   482,   599,   599,   599,   599,   841,   661,
     485,    21,    15,    15,   361,     8,    21,     7,    21,    21,
     559,   438,   431,   559,   421,    26,    21,   439,   426,   440,
     440,   441,   441,   441,    21,   482,     5,   482,   500,   621,
     622,   485,     8,   661,   485,     8,   482,   604,   361,    21,
     254,   482,     8,    21,   482,    15,    41,   135,   191,   209,
     221,   223,   224,   226,   229,   320,   482,   447,    21,    21,
      15,     8,   132,   748,    21,    21,     7,    21,   680,   682,
     354,   456,     5,    16,    17,    22,    24,    33,    35,    37,
     159,   162,   247,   305,   306,   307,   783,    21,    94,   230,
     284,   295,   795,    37,   191,   288,   299,   777,    21,    21,
      21,    21,   486,   661,   682,     7,     7,   394,    21,   478,
     425,   439,    21,     8,     8,    21,   465,   550,   255,    15,
      21,   752,     5,   482,   649,   650,    15,   665,    15,    15,
      15,    15,    15,   686,   686,    15,    15,     8,   481,   592,
     690,   691,    15,   701,   679,   679,     7,     8,    21,   827,
      21,     8,    21,     8,     7,   395,    21,    21,   482,   622,
     482,   354,   605,   606,   482,     8,    21,   599,   665,   700,
     718,   661,   700,   701,   690,   687,   482,   482,   660,   482,
      21,     8,   361,    21,     7,     8,    21,   661,   782,   482,
     361,   482,   486,   354,   632,   633,    21,     8,    15,    21,
     650,   148,   180,   666,     7,    21,    21,     7,    21,    15,
      21,    21,     8,    21,     8,   690,    78,   681,   681,    21,
     327,    21,     8,   482,    40,   482,   607,   608,   753,     7,
       7,   667,   668,   690,   718,   701,   576,   482,   482,    21,
      21,    21,    15,   633,   354,   609,     8,    21,     8,    21,
      15,    21,    21,    21,     8,   481,    17,   610,   611,   608,
     668,   482,   669,   670,    21,   482,    21,   612,    17,     7,
       8,    21,     8,   755,   612,   482,   670,    15,   361,   361,
     671,   672,   673,   674,   675,   182,   318,   128,   157,   217,
       8,    21,     7,     7,    15,   676,   676,   676,   672,   361,
     674,   675,   361,   675,   480,     7,    21,   675
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
#line 770 "gram1.y"
    { (yyval.bf_node) = BFNULL; ;}
    break;

  case 3:
#line 772 "gram1.y"
    { (yyval.bf_node) = set_stat_list((yyvsp[(1) - (3)].bf_node),(yyvsp[(2) - (3)].bf_node)); ;}
    break;

  case 4:
#line 776 "gram1.y"
    { lastwasbranch = NO;  (yyval.bf_node) = BFNULL; ;}
    break;

  case 5:
#line 778 "gram1.y"
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
#line 792 "gram1.y"
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
#line 823 "gram1.y"
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
#line 832 "gram1.y"
    {
	      err("Unclassifiable statement", 10);
	      flline();
	      (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 9:
#line 838 "gram1.y"
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
#line 858 "gram1.y"
    { 
	      flline();	 needkwd = NO;	inioctl = NO;
/*!!!*/
              opt_kwd_ = NO; intonly = NO; opt_kwd_hedr = NO; opt_kwd_r = NO; as_op_kwd_= NO; optcorner = NO;
	      yyerrok; yyclearin;  (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 11:
#line 867 "gram1.y"
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
#line 883 "gram1.y"
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
#line 895 "gram1.y"
    {  PTR_BFND q = BFNULL;

	      (yyvsp[(3) - (3)].symbol)->variant = PROCEDURE_NAME;
	      (yyvsp[(3) - (3)].symbol)->decl = YES;   /* variable declaration has been seen. */
	      q = get_bfnd(fi,BLOCK_DATA, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
	      set_blobs(q, global_bfnd, NEW_GROUP1);
              add_scope_level(q, NO);
	    ;}
    break;

  case 14:
#line 905 "gram1.y"
    { 
              install_param_list((yyvsp[(3) - (4)].symbol), (yyvsp[(4) - (4)].symbol), LLNULL, PROCEDURE_NAME); 
	      /* if there is only a control end the control parent is not set */
              
	     ;}
    break;

  case 15:
#line 912 "gram1.y"
    { install_param_list((yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].symbol), LLNULL, PROCEDURE_NAME); 
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP) 
                   (yyvsp[(4) - (5)].symbol)->attr = (yyvsp[(4) - (5)].symbol)->attr | RECURSIVE_BIT;
              pred_bfnd->entry.Template.ll_ptr3 = (yyvsp[(1) - (5)].ll_node);
            ;}
    break;

  case 16:
#line 918 "gram1.y"
    {
              install_param_list((yyvsp[(3) - (5)].symbol), (yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].ll_node), FUNCTION_NAME);  
  	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(5) - (5)].ll_node);
            ;}
    break;

  case 17:
#line 923 "gram1.y"
    {
              install_param_list((yyvsp[(1) - (3)].symbol), (yyvsp[(2) - (3)].symbol), (yyvsp[(3) - (3)].ll_node), FUNCTION_NAME); 
	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
	    ;}
    break;

  case 18:
#line 928 "gram1.y"
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
#line 952 "gram1.y"
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
#line 978 "gram1.y"
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
#line 993 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, RECURSIVE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 22:
#line 995 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PURE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 23:
#line 997 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, ELEMENTAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 24:
#line 1001 "gram1.y"
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
#line 1018 "gram1.y"
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
#line 1032 "gram1.y"
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
#line 1056 "gram1.y"
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
#line 1072 "gram1.y"
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
#line 1086 "gram1.y"
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
#line 1104 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 31:
#line 1106 "gram1.y"
    { PTR_SYMB s;
              s = make_scalar((yyvsp[(4) - (5)].hash_entry), TYNULL, LOCAL);
              (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 32:
#line 1113 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 33:
#line 1116 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_MAIN")); ;}
    break;

  case 34:
#line 1118 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry));
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
            ;}
    break;

  case 35:
#line 1124 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_BLOCK")); ;}
    break;

  case 36:
#line 1126 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry)); 
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
	    ;}
    break;

  case 37:
#line 1133 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 38:
#line 1135 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 39:
#line 1137 "gram1.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); ;}
    break;

  case 41:
#line 1142 "gram1.y"
    { (yyval.symbol) = set_id_list((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); ;}
    break;

  case 42:
#line 1146 "gram1.y"
    {
	      (yyval.symbol) = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, IO);
            ;}
    break;

  case 43:
#line 1150 "gram1.y"
    { (yyval.symbol) = make_scalar(look_up_sym("*"), TYNULL, IO); ;}
    break;

  case 44:
#line 1156 "gram1.y"
    { char *s;

	      s = copyn(yyleng+1, yytext);
	      s[yyleng] = '\0';
	      (yyval.charp) = s;
	    ;}
    break;

  case 45:
#line 1165 "gram1.y"
    { needkwd = 1; ;}
    break;

  case 46:
#line 1169 "gram1.y"
    { needkwd = NO; ;}
    break;

  case 47:
#line 1174 "gram1.y"
    { colon_flag = YES; ;}
    break;

  case 61:
#line 1195 "gram1.y"
    {
	      saveall = YES;
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 62:
#line 1200 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, (yyvsp[(4) - (4)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 63:
#line 1205 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL, SMNULL);
	      p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,FORMAT_STAT, SMNULL, p, LLNULL, LLNULL);
             ;}
    break;

  case 64:
#line 1212 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,PARAM_DECL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 77:
#line 1228 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, SMNULL, LLNULL, LLNULL, LLNULL); 
             /* add_scope_level($$, NO); */    
            ;}
    break;

  case 78:
#line 1232 "gram1.y"
    { PTR_SYMB s;

	      s = make_procedure((yyvsp[(3) - (3)].hash_entry), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 79:
#line 1240 "gram1.y"
    { PTR_SYMB s;

	      s = make_function((yyvsp[(4) - (5)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_OPERATOR, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 80:
#line 1248 "gram1.y"
    { PTR_SYMB s;


	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_ASSIGNMENT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 81:
#line 1257 "gram1.y"
    { parstate = INDCL;
              (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      /*process_interface($$);*/ /*podd 01.02.03*/
              /*delete_beyond_scope_level(pred_bfnd);*/
	    ;}
    break;

  case 82:
#line 1265 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 83:
#line 1269 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 84:
#line 1271 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 85:
#line 1275 "gram1.y"
    { (yyval.hash_entry) = look_up_op(PLUS); ;}
    break;

  case 86:
#line 1277 "gram1.y"
    { (yyval.hash_entry) = look_up_op(MINUS); ;}
    break;

  case 87:
#line 1279 "gram1.y"
    { (yyval.hash_entry) = look_up_op(ASTER); ;}
    break;

  case 88:
#line 1281 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DASTER); ;}
    break;

  case 89:
#line 1283 "gram1.y"
    { (yyval.hash_entry) = look_up_op(SLASH); ;}
    break;

  case 90:
#line 1285 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DSLASH); ;}
    break;

  case 91:
#line 1287 "gram1.y"
    { (yyval.hash_entry) = look_up_op(AND); ;}
    break;

  case 92:
#line 1289 "gram1.y"
    { (yyval.hash_entry) = look_up_op(OR); ;}
    break;

  case 93:
#line 1291 "gram1.y"
    { (yyval.hash_entry) = look_up_op(XOR); ;}
    break;

  case 94:
#line 1293 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NOT); ;}
    break;

  case 95:
#line 1295 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQ); ;}
    break;

  case 96:
#line 1297 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NE); ;}
    break;

  case 97:
#line 1299 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GT); ;}
    break;

  case 98:
#line 1301 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GE); ;}
    break;

  case 99:
#line 1303 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LT); ;}
    break;

  case 100:
#line 1305 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LE); ;}
    break;

  case 101:
#line 1307 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NEQV); ;}
    break;

  case 102:
#line 1309 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQV); ;}
    break;

  case 103:
#line 1314 "gram1.y"
    {
             PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, LLNULL, LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 104:
#line 1323 "gram1.y"
    { PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, (yyvsp[(5) - (7)].ll_node), LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 105:
#line 1333 "gram1.y"
    {
	     (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);
           ;}
    break;

  case 106:
#line 1341 "gram1.y"
    {
             (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);	
           ;}
    break;

  case 107:
#line 1351 "gram1.y"
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
#line 1372 "gram1.y"
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
#line 1391 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 110:
#line 1393 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 111:
#line 1395 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node); ;}
    break;

  case 112:
#line 1399 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 113:
#line 1401 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); ;}
    break;

  case 114:
#line 1405 "gram1.y"
    { type_options = type_options | PARAMETER_BIT; 
              (yyval.ll_node) = make_llnd(fi, PARAMETER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 115:
#line 1409 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 116:
#line 1411 "gram1.y"
    { type_options = type_options | ALLOCATABLE_BIT;
              (yyval.ll_node) = make_llnd(fi, ALLOCATABLE_OP, LLNULL, LLNULL, SMNULL);
	    ;}
    break;

  case 117:
#line 1415 "gram1.y"
    { type_options = type_options | DIMENSION_BIT;
	      attr_ndim = ndim;
	      attr_dims = (yyvsp[(2) - (2)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DIMENSION_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 118:
#line 1421 "gram1.y"
    { type_options = type_options | EXTERNAL_BIT;
              (yyval.ll_node) = make_llnd(fi, EXTERNAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 119:
#line 1425 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node); ;}
    break;

  case 120:
#line 1427 "gram1.y"
    { type_options = type_options | INTRINSIC_BIT;
              (yyval.ll_node) = make_llnd(fi, INTRINSIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 121:
#line 1431 "gram1.y"
    { type_options = type_options | OPTIONAL_BIT;
              (yyval.ll_node) = make_llnd(fi, OPTIONAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 122:
#line 1435 "gram1.y"
    { type_options = type_options | POINTER_BIT;
              (yyval.ll_node) = make_llnd(fi, POINTER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 123:
#line 1439 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, SAVE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 124:
#line 1443 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, STATIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 125:
#line 1447 "gram1.y"
    { type_options = type_options | TARGET_BIT; 
              (yyval.ll_node) = make_llnd(fi, TARGET_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 126:
#line 1453 "gram1.y"
    { type_options = type_options | IN_BIT;  type_opt = IN_BIT; 
              (yyval.ll_node) = make_llnd(fi, IN_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 127:
#line 1457 "gram1.y"
    { type_options = type_options | OUT_BIT;  type_opt = OUT_BIT; 
              (yyval.ll_node) = make_llnd(fi, OUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 128:
#line 1461 "gram1.y"
    { type_options = type_options | INOUT_BIT;  type_opt = INOUT_BIT;
              (yyval.ll_node) = make_llnd(fi, INOUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 129:
#line 1467 "gram1.y"
    { type_options = type_options | PUBLIC_BIT; 
              type_opt = PUBLIC_BIT;
              (yyval.ll_node) = make_llnd(fi, PUBLIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 130:
#line 1472 "gram1.y"
    { type_options =  type_options | PRIVATE_BIT;
               type_opt = PRIVATE_BIT;
              (yyval.ll_node) = make_llnd(fi, PRIVATE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 131:
#line 1479 "gram1.y"
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
#line 1490 "gram1.y"
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
#line 1503 "gram1.y"
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
#line 1514 "gram1.y"
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
#line 1527 "gram1.y"
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
#line 1537 "gram1.y"
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
#line 1550 "gram1.y"
    {
	      privateall = 1;
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 138:
#line 1555 "gram1.y"
    {
	      /*type_options = type_options | PRIVATE_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 139:
#line 1561 "gram1.y"
    {type_opt = PRIVATE_BIT;;}
    break;

  case 140:
#line 1565 "gram1.y"
    { 
	      (yyval.bf_node) = get_bfnd(fi, SEQUENCE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
            ;}
    break;

  case 141:
#line 1570 "gram1.y"
    {
	      /*saveall = YES;*/ /*14.03.03*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 142:
#line 1575 "gram1.y"
    {
	      /*type_options = type_options | PUBLIC_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 143:
#line 1581 "gram1.y"
    {type_opt = PUBLIC_BIT;;}
    break;

  case 144:
#line 1585 "gram1.y"
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
#line 1595 "gram1.y"
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
#line 1608 "gram1.y"
    {opt_kwd_hedr = YES;;}
    break;

  case 147:
#line 1613 "gram1.y"
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
#line 1632 "gram1.y"
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
#line 1658 "gram1.y"
    { (yyval.token) = ATT_GLOBAL; ;}
    break;

  case 150:
#line 1660 "gram1.y"
    { (yyval.token) = ATT_CLUSTER; ;}
    break;

  case 151:
#line 1672 "gram1.y"
    {
/*		  varleng = ($1<0 || $1==TYLONG ? 0 : typesize[$1]); */
		  vartype = (yyvsp[(1) - (1)].data_type);
		;}
    break;

  case 152:
#line 1679 "gram1.y"
    { (yyval.data_type) = global_int; ;}
    break;

  case 153:
#line 1680 "gram1.y"
    { (yyval.data_type) = global_float; ;}
    break;

  case 154:
#line 1681 "gram1.y"
    { (yyval.data_type) = global_complex; ;}
    break;

  case 155:
#line 1682 "gram1.y"
    { (yyval.data_type) = global_double; ;}
    break;

  case 156:
#line 1683 "gram1.y"
    { (yyval.data_type) = global_dcomplex; ;}
    break;

  case 157:
#line 1684 "gram1.y"
    { (yyval.data_type) = global_bool; ;}
    break;

  case 158:
#line 1685 "gram1.y"
    { (yyval.data_type) = global_string; ;}
    break;

  case 159:
#line 1690 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 160:
#line 1692 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 161:
#line 1696 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(3) - (5)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 162:
#line 1698 "gram1.y"
    { PTR_LLND l;

                 l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL); 
                 l->entry.string_val = (char *)"*";
                 (yyval.ll_node) = make_llnd(fi, LEN_OP, l,l, SMNULL);
                ;}
    break;

  case 163:
#line 1705 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(5) - (6)].ll_node), (yyvsp[(5) - (6)].ll_node), SMNULL);;}
    break;

  case 164:
#line 1709 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 165:
#line 1711 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 166:
#line 1713 "gram1.y"
    { /*$$ = make_llnd(fi, PAREN_OP, $2, LLNULL, SMNULL);*/  (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node);  ;}
    break;

  case 167:
#line 1721 "gram1.y"
    { if((yyvsp[(7) - (9)].ll_node)->variant==LENGTH_OP && (yyvsp[(3) - (9)].ll_node)->variant==(yyvsp[(7) - (9)].ll_node)->variant)
                (yyvsp[(7) - (9)].ll_node)->variant=KIND_OP;
                (yyval.ll_node) = make_llnd(fi, CONS, (yyvsp[(3) - (9)].ll_node), (yyvsp[(7) - (9)].ll_node), SMNULL); 
            ;}
    break;

  case 168:
#line 1728 "gram1.y"
    { if(vartype->variant == T_STRING)
                (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
              else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
            ;}
    break;

  case 169:
#line 1734 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 170:
#line 1740 "gram1.y"
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
#line 1749 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 172:
#line 1757 "gram1.y"
    {endioctl();;}
    break;

  case 173:
#line 1770 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 174:
#line 1772 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node); ;}
    break;

  case 175:
#line 1775 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, POINTST_OP, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 176:
#line 1779 "gram1.y"
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
#line 1794 "gram1.y"
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
#line 1810 "gram1.y"
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
#line 1828 "gram1.y"
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
#line 1848 "gram1.y"
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
#line 1868 "gram1.y"
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
#line 1890 "gram1.y"
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
#line 1907 "gram1.y"
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
#line 1925 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 185:
#line 1932 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 186:
#line 1939 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(q, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 187:
#line 1946 "gram1.y"
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
#line 1959 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,NAMELIST_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 189:
#line 1966 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(r, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 190:
#line 1973 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(q, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 191:
#line 1984 "gram1.y"
    { (yyval.symbol) =  make_local_entity((yyvsp[(2) - (3)].hash_entry), NAMELIST_NAME,global_default,LOCAL); ;}
    break;

  case 192:
#line 1988 "gram1.y"
    { (yyval.symbol) = NULL; /*make_common(look_up_sym("*"));*/ ;}
    break;

  case 193:
#line 1990 "gram1.y"
    { (yyval.symbol) = make_common((yyvsp[(2) - (3)].hash_entry)); ;}
    break;

  case 194:
#line 1995 "gram1.y"
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
#line 2013 "gram1.y"
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
#line 2024 "gram1.y"
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
#line 2036 "gram1.y"
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
#line 2048 "gram1.y"
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
#line 2062 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,EQUI_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node),
			     LLNULL, LLNULL);
	    ;}
    break;

  case 200:
#line 2068 "gram1.y"
    { 
	      add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 201:
#line 2075 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EQUI_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
           ;}
    break;

  case 202:
#line 2081 "gram1.y"
    { PTR_LLND p;
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (3)].ll_node), p, SMNULL);
	    ;}
    break;

  case 203:
#line 2087 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 204:
#line 2095 "gram1.y"
    {  PTR_SYMB s;
           s=make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
           (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$=$1; $$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 205:
#line 2102 "gram1.y"
    {  PTR_SYMB s;
           s=make_array((yyvsp[(1) - (4)].hash_entry),TYNULL,LLNULL,0,LOCAL);
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 207:
#line 2121 "gram1.y"
    { PTR_LLND p;
              data_stat = NO;
	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL,
			    SMNULL);
              p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,DATA_DECL, SMNULL, p, LLNULL, LLNULL);
            ;}
    break;

  case 210:
#line 2135 "gram1.y"
    {data_stat = YES;;}
    break;

  case 211:
#line 2139 "gram1.y"
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
#line 2184 "gram1.y"
    {;;}
    break;

  case 223:
#line 2188 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);;}
    break;

  case 224:
#line 2192 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL); 
              (yyval.symbol)->attr = (yyval.symbol)->attr | DATA_BIT; 
            ;}
    break;

  case 225:
#line 2198 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_SUBS, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 226:
#line 2202 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_RANGE, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 227:
#line 2206 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 228:
#line 2208 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 229:
#line 2212 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 230:
#line 2214 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 231:
#line 2218 "gram1.y"
    {(yyval.ll_node)= make_llnd(fi, DATA_IMPL_DO, (yyvsp[(2) - (7)].ll_node), (yyvsp[(6) - (7)].ll_node), (yyvsp[(4) - (7)].symbol)); ;}
    break;

  case 232:
#line 2222 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 233:
#line 2224 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 234:
#line 2228 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 235:
#line 2230 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 236:
#line 2232 "gram1.y"
    {
              (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr2 = (yyvsp[(3) - (3)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); 
            ;}
    break;

  case 237:
#line 2237 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 251:
#line 2261 "gram1.y"
    {if((yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->variant != TYPE_NAME)
               errstr("Undefined type %s",(yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->ident,319); 
           ;}
    break;

  case 268:
#line 2306 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ICON_EXPR, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 269:
#line 2308 "gram1.y"
    {
              PTR_LLND p;

              p = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 270:
#line 2315 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 271:
#line 2322 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 272:
#line 2329 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 273:
#line 2338 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 274:
#line 2340 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 275:
#line 2342 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 276:
#line 2346 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 277:
#line 2348 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 278:
#line 2352 "gram1.y"
    {
              PTR_LLND p;

              p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
              p->entry.ival = atoi(yytext);
              p->type = global_int;
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 279:
#line 2361 "gram1.y"
    {
              PTR_LLND p;
 
              p = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 280:
#line 2368 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 281:
#line 2375 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 282:
#line 2377 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 283:
#line 2381 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
             (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
           ;}
    break;

  case 284:
#line 2385 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol)); 
            (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
          ;}
    break;

  case 285:
#line 2391 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 286:
#line 2393 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), EXPR_LIST); ;}
    break;

  case 287:
#line 2397 "gram1.y"
    { as_op_kwd_ = YES; ;}
    break;

  case 288:
#line 2401 "gram1.y"
    { as_op_kwd_ = NO; ;}
    break;

  case 289:
#line 2406 "gram1.y"
    { 
             PTR_SYMB s; 
             s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
	     (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 290:
#line 2413 "gram1.y"
    { PTR_SYMB s;
	      s = make_function((yyvsp[(3) - (4)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,OPERATOR_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 291:
#line 2420 "gram1.y"
    { PTR_SYMB s;
	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,ASSIGNMENT_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 292:
#line 2430 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 293:
#line 2432 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 294:
#line 2436 "gram1.y"
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
#line 2448 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, MODULE_PROC_STMT, SMNULL, (yyvsp[(2) - (2)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 296:
#line 2451 "gram1.y"
    { PTR_SYMB s;
 	      PTR_LLND q;

	      s = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	    ;}
    break;

  case 297:
#line 2460 "gram1.y"
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
#line 2473 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
              /*add_scope_level($3->entry.Template.func_hedr, YES);*/ /*17.06.01*/
              copy_module_scope((yyvsp[(3) - (3)].symbol),LLNULL); /*17.03.03*/
              colon_flag = NO;
            ;}
    break;

  case 299:
#line 2479 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), (yyvsp[(6) - (6)].ll_node), LLNULL, LLNULL); 
              /*add_scope_level(module_scope, YES); *//* 17.06.01*/
              copy_module_scope((yyvsp[(3) - (6)].symbol),(yyvsp[(6) - (6)].ll_node)); /*17.03.03 */
              colon_flag = NO;
            ;}
    break;

  case 300:
#line 2485 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, LLNULL, LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 301:
#line 2491 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, (yyvsp[(7) - (7)].ll_node), LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (7)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 302:
#line 2499 "gram1.y"
    {
              if ((yyvsp[(1) - (1)].hash_entry)->id_attr == SMNULL)
	         warn1("Unknown module %s", (yyvsp[(1) - (1)].hash_entry)->ident,308);
              (yyval.symbol) = make_global_entity((yyvsp[(1) - (1)].hash_entry), MODULE_NAME, global_default, NO);
	      module_scope = (yyval.symbol)->entry.Template.func_hedr;
           
            ;}
    break;

  case 303:
#line 2509 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 304:
#line 2511 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 305:
#line 2515 "gram1.y"
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
#line 2536 "gram1.y"
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
#line 2561 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 308:
#line 2563 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 309:
#line 2567 "gram1.y"
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
#line 2598 "gram1.y"
    { ndim = 0;	explicit_shape = 1; (yyval.ll_node) = LLNULL; ;}
    break;

  case 311:
#line 2600 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 312:
#line 2603 "gram1.y"
    { ndim = 0; explicit_shape = 1;;}
    break;

  case 313:
#line 2604 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
	    ;}
    break;

  case 314:
#line 2609 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 315:
#line 2613 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
	      ++ndim;
	    ;}
    break;

  case 316:
#line 2621 "gram1.y"
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
#line 2630 "gram1.y"
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
#line 2639 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      ++ndim;
	    ;}
    break;

  case 319:
#line 2649 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,STAR_RANGE, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
              explicit_shape = 0;
	    ;}
    break;

  case 321:
#line 2658 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 322:
#line 2660 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 323:
#line 2664 "gram1.y"
    {PTR_LABEL p;
	     p = make_label_node(fi,convci(yyleng, yytext));
	     p->scope = cur_scope();
	     (yyval.ll_node) = make_llnd_label(fi,LABEL_REF, p);
	  ;}
    break;

  case 324:
#line 2672 "gram1.y"
    { /*PTR_LLND l;*/

          /*   l = make_llnd(fi, EXPR_LIST, $3, LLNULL, SMNULL);*/
             (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
             redefine_func_arg_type();
           ;}
    break;

  case 325:
#line 2687 "gram1.y"
    { /*undeftype = YES;
	    setimpl(TYNULL, (int)'a', (int)'z'); FB COMMENTED---> NOT QUITE RIGHT BUT AVOID PB WITH COMMON*/
	    (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	  ;}
    break;

  case 326:
#line 2694 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 327:
#line 2696 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 328:
#line 2700 "gram1.y"
    { 

            (yyval.ll_node) = make_llnd(fi, IMPL_TYPE, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
            (yyval.ll_node)->type = vartype;
          ;}
    break;

  case 329:
#line 2715 "gram1.y"
    { implkwd = YES; ;}
    break;

  case 330:
#line 2716 "gram1.y"
    { vartype = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 331:
#line 2720 "gram1.y"
    { (yyval.data_type) = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 332:
#line 2722 "gram1.y"
    { (yyval.data_type) = (yyvsp[(1) - (1)].data_type);;}
    break;

  case 333:
#line 2734 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 334:
#line 2736 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 335:
#line 2740 "gram1.y"
    {
	      setimpl(vartype, (int)(yyvsp[(1) - (1)].charv), (int)(yyvsp[(1) - (1)].charv));
	      (yyval.ll_node) = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.cval = (yyvsp[(1) - (1)].charv);
	    ;}
    break;

  case 336:
#line 2746 "gram1.y"
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
#line 2758 "gram1.y"
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
#line 2769 "gram1.y"
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
#line 2786 "gram1.y"
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
#line 2824 "gram1.y"
    { (yyval.ll_node) = LLNULL; endioctl(); ;}
    break;

  case 343:
#line 2826 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);  endioctl();;}
    break;

  case 344:
#line 2830 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 345:
#line 2832 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 346:
#line 2834 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
	      l->type = (yyvsp[(2) - (2)].ll_node)->type;
              (yyval.ll_node) = l; 
	    ;}
    break;

  case 347:
#line 2845 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 348:
#line 2849 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 349:
#line 2855 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 350:
#line 2857 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 351:
#line 2861 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 352:
#line 2863 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 353:
#line 2865 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 354:
#line 2869 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 355:
#line 2871 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 356:
#line 2875 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 357:
#line 2877 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 358:
#line 2879 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 359:
#line 2881 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 360:
#line 2883 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 361:
#line 2885 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 362:
#line 2887 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(1) - (2)].hash_entry), (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 363:
#line 2889 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 364:
#line 2891 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 365:
#line 2893 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eq.", EQ_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 366:
#line 2895 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".gt.", GT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 367:
#line 2897 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".lt.", LT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 368:
#line 2899 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", GTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 369:
#line 2901 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", LTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 370:
#line 2903 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ne.", NOTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 371:
#line 2905 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eqv.", EQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 372:
#line 2907 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".neqv.", NEQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 373:
#line 2909 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".xor.", XOR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 374:
#line 2911 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".or.", OR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 375:
#line 2913 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".and.", AND_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 376:
#line 2915 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".not.", NOT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 377:
#line 2917 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("//", CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 378:
#line 2919 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(2) - (3)].hash_entry), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 379:
#line 2922 "gram1.y"
    { (yyval.token) = ADD_OP; ;}
    break;

  case 380:
#line 2923 "gram1.y"
    { (yyval.token) = SUBT_OP; ;}
    break;

  case 381:
#line 2935 "gram1.y"
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
#line 3009 "gram1.y"
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
#line 3021 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 384:
#line 3023 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 385:
#line 3027 "gram1.y"
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
#line 3158 "gram1.y"
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
#line 3208 "gram1.y"
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
#line 3252 "gram1.y"
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
#line 3294 "gram1.y"
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
#line 3352 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 391:
#line 3354 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 392:
#line 3356 "gram1.y"
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
#line 3396 "gram1.y"
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
#line 3438 "gram1.y"
    { 
	      if ((yyvsp[(1) - (2)].ll_node)->type->variant == T_STRING) {
                 (yyvsp[(1) - (2)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (2)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node); (yyval.ll_node)->type = global_string;
              }
              else errstr("can't subscript of %s", (yyvsp[(1) - (2)].ll_node)->entry.Template.symbol->ident,44);
            ;}
    break;

  case 395:
#line 3448 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 396:
#line 3450 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 397:
#line 3454 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 398:
#line 3458 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 399:
#line 3460 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 400:
#line 3464 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 401:
#line 3466 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 402:
#line 3472 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 403:
#line 3474 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 404:
#line 3480 "gram1.y"
    {
              if ((yyvsp[(2) - (2)].ll_node) != LLNULL)
		 (yyval.ll_node) = make_llnd(fi, ARRAY_OP, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); 
	      else 
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);
             ;}
    break;

  case 405:
#line 3490 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 1;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 406:
#line 3496 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 0;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 407:
#line 3503 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,FLOAT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_float;
	    ;}
    break;

  case 408:
#line 3509 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DOUBLE_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_double;
	    ;}
    break;

  case 409:
#line 3517 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.ival = atoi(yytext);
	      (yyval.ll_node)->type = global_int;
	    ;}
    break;

  case 410:
#line 3525 "gram1.y"
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
#line 3541 "gram1.y"
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
#line 3551 "gram1.y"
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
#line 3564 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,COMPLEX_VAL, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL);
	      (yyval.ll_node)->type = global_complex;
	    ;}
    break;

  case 414:
#line 3571 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 415:
#line 3573 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 416:
#line 3596 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 417:
#line 3598 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 418:
#line 3600 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),SMNULL),(yyvsp[(5) - (5)].ll_node),SMNULL); ;}
    break;

  case 419:
#line 3602 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (4)].ll_node),LLNULL,SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 420:
#line 3604 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (4)].ll_node),SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 421:
#line 3606 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 422:
#line 3608 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (2)].ll_node),SMNULL); ;}
    break;

  case 423:
#line 3610 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL); ;}
    break;

  case 424:
#line 3613 "gram1.y"
    {in_vec=YES;;}
    break;

  case 425:
#line 3613 "gram1.y"
    {in_vec=NO;;}
    break;

  case 426:
#line 3614 "gram1.y"
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
#line 3628 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 428:
#line 3630 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 429:
#line 3653 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 430:
#line 3655 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 431:
#line 3657 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                  endioctl();
                ;}
    break;

  case 432:
#line 3673 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 433:
#line 3675 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 434:
#line 3677 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
             endioctl();
           ;}
    break;

  case 435:
#line 3690 "gram1.y"
    {stat_alloc = LLNULL;;}
    break;

  case 436:
#line 3694 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 437:
#line 3696 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 438:
#line 3704 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 439:
#line 3706 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 440:
#line 3708 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 441:
#line 3710 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 442:
#line 3764 "gram1.y"
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
#line 3786 "gram1.y"
    {
              make_extend((yyvsp[(3) - (3)].symbol));
              (yyval.bf_node) = BFNULL; 
              /* delete_beyond_scope_level(pred_bfnd); */
             ;}
    break;

  case 444:
#line 3799 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	    bind(); 
	    delete_beyond_scope_level(pred_bfnd);
	    position = IN_OUTSIDE;
          ;}
    break;

  case 445:
#line 3808 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 446:
#line 3811 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 447:
#line 3861 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = LOGIF_NODE;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 448:
#line 3867 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 449:
#line 3872 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (3)].ll_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 450:
#line 3890 "gram1.y"
    { make_elseif((yyvsp[(4) - (7)].ll_node),(yyvsp[(7) - (7)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL;;}
    break;

  case 451:
#line 3892 "gram1.y"
    { make_else((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 452:
#line 3894 "gram1.y"
    { make_endif((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 453:
#line 3896 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 454:
#line 3898 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CONTAINS_STMT, SMNULL, LLNULL, LLNULL, LLNULL); ;}
    break;

  case 455:
#line 3901 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = FORALL_STAT;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 456:
#line 3907 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 457:
#line 3909 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node); (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 458:
#line 3911 "gram1.y"
    { make_endforall((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 459:
#line 3914 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 460:
#line 3916 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 461:
#line 3918 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 462:
#line 3945 "gram1.y"
    { 	     
	     /*  if($5 && $5->labdefined)
		 execerr("no backward DO loops", (char *)NULL); */
	       (yyval.bf_node) = make_do(WHILE_NODE, LBNULL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL);
	       /*$$->entry.Template.ll_ptr3 = $1;*/	     
           ;}
    break;

  case 463:
#line 3954 "gram1.y"
    {
               if( (yyvsp[(4) - (7)].label) && (yyvsp[(4) - (7)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(WHILE_NODE, (yyvsp[(4) - (7)].label), SMNULL, (yyvsp[(7) - (7)].ll_node), LLNULL, LLNULL);            
	    ;}
    break;

  case 464:
#line 3962 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 465:
#line 3964 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(5) - (6)].ll_node);;}
    break;

  case 466:
#line 3966 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 467:
#line 3971 "gram1.y"
    {  
               if( (yyvsp[(4) - (11)].label) && (yyvsp[(4) - (11)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (11)].label), (yyvsp[(7) - (11)].symbol), (yyvsp[(9) - (11)].ll_node), (yyvsp[(11) - (11)].ll_node), LLNULL);            
	    ;}
    break;

  case 468:
#line 3978 "gram1.y"
    {
               if( (yyvsp[(4) - (13)].label) && (yyvsp[(4) - (13)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (13)].label), (yyvsp[(7) - (13)].symbol), (yyvsp[(9) - (13)].ll_node), (yyvsp[(11) - (13)].ll_node), (yyvsp[(13) - (13)].ll_node));            
	    ;}
    break;

  case 469:
#line 3986 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CASE_NODE, (yyvsp[(4) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 470:
#line 3988 "gram1.y"
    { /*PTR_LLND p;*/
	     /* p = make_llnd(fi, DEFAULT, LLNULL, LLNULL, SMNULL); */
	      (yyval.bf_node) = get_bfnd(fi, DEFAULT_NODE, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 471:
#line 3992 "gram1.y"
    { make_endselect((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 472:
#line 3995 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(6) - (7)].ll_node), LLNULL, LLNULL) ; ;}
    break;

  case 473:
#line 3997 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(7) - (8)].ll_node), LLNULL, (yyvsp[(1) - (8)].ll_node)) ; ;}
    break;

  case 474:
#line 4001 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 475:
#line 4007 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 476:
#line 4009 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 477:
#line 4011 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 478:
#line 4013 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL); ;}
    break;

  case 479:
#line 4017 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 480:
#line 4019 "gram1.y"
    { PTR_LLND p;
	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 481:
#line 4027 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 482:
#line 4029 "gram1.y"
    { (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSTRUCT_NAME, global_default,
                                     LOCAL); ;}
    break;

  case 483:
#line 4035 "gram1.y"
    {(yyval.hash_entry) = HSNULL;;}
    break;

  case 484:
#line 4037 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry);;}
    break;

  case 485:
#line 4041 "gram1.y"
    {(yyval.hash_entry) = look_up_sym(yytext);;}
    break;

  case 486:
#line 4045 "gram1.y"
    { PTR_SYMB s;
	             s = make_local_entity( (yyvsp[(1) - (2)].hash_entry), CONSTRUCT_NAME, global_default, LOCAL);             
                    (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
                   ;}
    break;

  case 487:
#line 4066 "gram1.y"
    { (yyval.bf_node) = make_if((yyvsp[(4) - (5)].ll_node)); ;}
    break;

  case 488:
#line 4069 "gram1.y"
    { (yyval.bf_node) = make_forall((yyvsp[(4) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node)); ;}
    break;

  case 489:
#line 4073 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 490:
#line 4075 "gram1.y"
    { PTR_LLND p;	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 491:
#line 4082 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, FORALL_OP, (yyvsp[(3) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); ;}
    break;

  case 492:
#line 4086 "gram1.y"
    { (yyval.ll_node)=LLNULL;;}
    break;

  case 493:
#line 4088 "gram1.y"
    { (yyval.ll_node)=(yyvsp[(2) - (2)].ll_node);;}
    break;

  case 494:
#line 4104 "gram1.y"
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
#line 4117 "gram1.y"
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
#line 4140 "gram1.y"
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
#line 4163 "gram1.y"
    { (yyval.label) = LBNULL; ;}
    break;

  case 498:
#line 4165 "gram1.y"
    {
	       (yyval.label)  = make_label_node(fi,convci(yyleng, yytext));
	       (yyval.label)->scope = cur_scope();
	    ;}
    break;

  case 499:
#line 4172 "gram1.y"
    { make_endwhere((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 500:
#line 4174 "gram1.y"
    { make_elsewhere((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 501:
#line 4176 "gram1.y"
    { make_elsewhere_mask((yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 502:
#line 4178 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 503:
#line 4180 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), LLNULL, (yyvsp[(1) - (6)].ll_node)); ;}
    break;

  case 504:
#line 4185 "gram1.y"
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
#line 4261 "gram1.y"
    { /*PTR_SYMB s;*/
	
	      /*s = make_scalar($2, TYNULL, LOCAL);*/
  	      (yyval.bf_node) = get_bfnd(fi, POINTER_ASSIGN_STAT, SMNULL, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), LLNULL);
	    ;}
    break;

  case 506:
#line 4273 "gram1.y"
    { PTR_SYMB p;

	      p = make_scalar((yyvsp[(5) - (5)].hash_entry), TYNULL, LOCAL);
	      p->variant = LABEL_VAR;
  	      (yyval.bf_node) = get_bfnd(fi,ASSLAB_STAT, p, (yyvsp[(3) - (5)].ll_node),LLNULL,LLNULL);
            ;}
    break;

  case 507:
#line 4280 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONT_STAT,SMNULL,LLNULL,LLNULL,LLNULL); ;}
    break;

  case 509:
#line 4283 "gram1.y"
    { inioctl = NO; ;}
    break;

  case 510:
#line 4285 "gram1.y"
    { PTR_LLND	p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(10) - (10)].ll_node), LLNULL, SMNULL);
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(8) - (10)].ll_node), p, SMNULL);
	      (yyval.bf_node)= get_bfnd(fi,ARITHIF_NODE, SMNULL, (yyvsp[(4) - (10)].ll_node),
			    make_llnd(fi,EXPR_LIST, (yyvsp[(6) - (10)].ll_node), p, SMNULL), LLNULL);
	      thiswasbranch = YES;
            ;}
    break;

  case 511:
#line 4294 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (1)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT, $1, LLNULL, LLNULL, LLNULL);
*/	      endioctl(); 
            ;}
    break;

  case 512:
#line 4301 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (3)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT,$1,LLNULL,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 513:
#line 4308 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, PLAIN);
/*	      match_parameters($1, $3);
	      $$= get_bfnd(fi,PROC_STAT,$1,$3,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 514:
#line 4316 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,RETURN_STAT,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = YES;
	    ;}
    break;

  case 515:
#line 4321 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,(yyvsp[(1) - (3)].token),SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = ((yyvsp[(1) - (3)].token) == STOP_STAT);
	    ;}
    break;

  case 516:
#line 4326 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CYCLE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 517:
#line 4329 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, EXIT_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 518:
#line 4332 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, ALLOCATE_STMT,  SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc, LLNULL); ;}
    break;

  case 519:
#line 4335 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, DEALLOCATE_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc , LLNULL); ;}
    break;

  case 520:
#line 4338 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, NULLIFY_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 521:
#line 4341 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_NODE, SMNULL, (yyvsp[(4) - (8)].ll_node), (yyvsp[(6) - (8)].ll_node), (yyvsp[(8) - (8)].ll_node)); ;}
    break;

  case 522:
#line 4359 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 523:
#line 4363 "gram1.y"
    {
	      (yyval.bf_node)=get_bfnd(fi,GOTO_NODE,SMNULL,LLNULL,LLNULL,(PTR_LLND)(yyvsp[(3) - (3)].ll_node));
	      thiswasbranch = YES;
	    ;}
    break;

  case 524:
#line 4368 "gram1.y"
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
#line 4387 "gram1.y"
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
#line 4406 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,COMGOTO_NODE, SMNULL, (yyvsp[(4) - (7)].ll_node), (yyvsp[(7) - (7)].ll_node), LLNULL); ;}
    break;

  case 529:
#line 4414 "gram1.y"
    { (yyval.symbol) = make_procedure((yyvsp[(3) - (4)].hash_entry), YES); ;}
    break;

  case 530:
#line 4418 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 531:
#line 4423 "gram1.y"
    { 
               (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
               endioctl();
            ;}
    break;

  case 532:
#line 4430 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 533:
#line 4432 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 534:
#line 4434 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,LABEL_ARG,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 535:
#line 4437 "gram1.y"
    { (yyval.token) = PAUSE_NODE; ;}
    break;

  case 536:
#line 4438 "gram1.y"
    { (yyval.token) = STOP_STAT; ;}
    break;

  case 537:
#line 4449 "gram1.y"
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
#line 4464 "gram1.y"
    { intonly = YES; ;}
    break;

  case 539:
#line 4468 "gram1.y"
    { intonly = NO; ;}
    break;

  case 540:
#line 4476 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 541:
#line 4479 "gram1.y"
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
#line 4489 "gram1.y"
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
#line 4502 "gram1.y"
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
#line 4515 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 545:
#line 4519 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 546:
#line 4522 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 547:
#line 4525 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 548:
#line 4529 "gram1.y"
    { (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (4)].ll_node);
		  (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (4)].bf_node); ;}
    break;

  case 549:
#line 4538 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 550:
#line 4541 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 551:
#line 4545 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 552:
#line 4547 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 553:
#line 4553 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 554:
#line 4557 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, BACKSPACE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 555:
#line 4559 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, REWIND_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 556:
#line 4561 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, ENDFILE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 557:
#line 4568 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 558:
#line 4572 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 559:
#line 4574 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, OPEN_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 560:
#line 4576 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, CLOSE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 561:
#line 4580 "gram1.y"
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
#line 4599 "gram1.y"
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
#line 4615 "gram1.y"
    { PTR_LLND p;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"unit";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, p, (yyvsp[(2) - (3)].ll_node), SMNULL);
		  endioctl();
		;}
    break;

  case 564:
#line 4626 "gram1.y"
    { 
		  (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);
		  endioctl();
		 ;}
    break;

  case 565:
#line 4633 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); endioctl();;}
    break;

  case 566:
#line 4635 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl();;}
    break;

  case 567:
#line 4639 "gram1.y"
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
#line 4665 "gram1.y"
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
#line 4680 "gram1.y"
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
#line 4695 "gram1.y"
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
#line 4712 "gram1.y"
    { PTR_LLND p;
                  
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 572:
#line 4720 "gram1.y"
    { PTR_LLND p;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 573:
#line 4729 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  (yyval.ll_node)->entry.string_val = copys(yytext);
		  (yyval.ll_node)->type = global_string;
	        ;}
    break;

  case 574:
#line 4737 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, READ_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 575:
#line 4742 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, WRITE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 576:
#line 4747 "gram1.y"
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
#line 4769 "gram1.y"
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
#line 4785 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);;}
    break;

  case 579:
#line 4787 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST);;}
    break;

  case 580:
#line 4791 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 581:
#line 4793 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
		;}
    break;

  case 582:
#line 4800 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);  (yyval.ll_node)->type = (yyvsp[(1) - (1)].ll_node)->type;;}
    break;

  case 583:
#line 4802 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 584:
#line 4804 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 585:
#line 4808 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 586:
#line 4810 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 587:
#line 4812 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 588:
#line 4814 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 589:
#line 4816 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 590:
#line 4818 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 591:
#line 4822 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);
	          (yyval.ll_node)->type = global_complex; ;}
    break;

  case 592:
#line 4825 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (3)].ll_node)->type; ;}
    break;

  case 593:
#line 4828 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 594:
#line 4834 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 595:
#line 4840 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 596:
#line 4848 "gram1.y"
    { inioctl = YES; ;}
    break;

  case 597:
#line 4852 "gram1.y"
    { startioctl();;}
    break;

  case 598:
#line 4860 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 599:
#line 4862 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 600:
#line 4866 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 601:
#line 4868 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 602:
#line 4870 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,(yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 603:
#line 4875 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 604:
#line 4880 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 605:
#line 4885 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 606:
#line 4890 "gram1.y"
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
#line 4899 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 608:
#line 4904 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 609:
#line 4909 "gram1.y"
    { comments = cur_comment = CMNULL; ;}
    break;

  case 610:
#line 4911 "gram1.y"
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

  case 674:
#line 4994 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 675:
#line 4996 "gram1.y"
    { PTR_SYMB s;
                if((yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2)
                {
                  s = (yyvsp[(3) - (3)].ll_node)->entry.Template.ll_ptr1->entry.Template.symbol;
                  s->attr = s->attr | COMMON_BIT;
                }
	        add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	      ;}
    break;

  case 676:
#line 5007 "gram1.y"
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

  case 677:
#line 5028 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DYNAMIC_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 678:
#line 5032 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 679:
#line 5034 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 680:
#line 5038 "gram1.y"
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

  case 681:
#line 5051 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INHERIT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 682:
#line 5055 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 683:
#line 5057 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 684:
#line 5061 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
              else
                s->attr = s->attr | INHERIT_BIT;        
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 685:
#line 5072 "gram1.y"
    { PTR_LLND q;
             q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              /* (void)fprintf(stderr,"hpf.gram: shadow\n");*/ 
	     (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_DIR,SMNULL,q,(yyvsp[(4) - (4)].ll_node),LLNULL);
            ;}
    break;

  case 686:
#line 5083 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 687:
#line 5087 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 688:
#line 5089 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 689:
#line 5093 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 690:
#line 5095 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 691:
#line 5097 "gram1.y"
    {
            if(parstate!=INEXEC) 
               err("Illegal shadow width specification", 56);  
            (yyval.ll_node) = make_llnd(fi,SHADOW_NAMES_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
          ;}
    break;

  case 692:
#line 5112 "gram1.y"
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

  case 693:
#line 5124 "gram1.y"
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
#line 5144 "gram1.y"
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

  case 695:
#line 5164 "gram1.y"
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

  case 696:
#line 5186 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 697:
#line 5192 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 698:
#line 5201 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 699:
#line 5209 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 700:
#line 5215 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 701:
#line 5223 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 702:
#line 5230 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 703:
#line 5236 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 704:
#line 5245 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 705:
#line 5249 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 706:
#line 5255 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 707:
#line 5263 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 708:
#line 5277 "gram1.y"
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

  case 709:
#line 5290 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 710:
#line 5296 "gram1.y"
    { PTR_LLND q;
             if(!(yyvsp[(4) - (5)].ll_node))
               err("Distribution format list is omitted", 51);
            /* if($6)
               err("NEW_VALUE specification in DISTRIBUTE directive");*/
             q = set_ll_list((yyvsp[(3) - (5)].ll_node),LLNULL,EXPR_LIST);
	     (yyval.bf_node) = get_bfnd(fi,DVM_DISTRIBUTE_DIR,SMNULL,q,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node));
            ;}
    break;

  case 711:
#line 5312 "gram1.y"
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

  case 712:
#line 5327 "gram1.y"
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

  case 713:
#line 5355 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 714:
#line 5357 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 715:
#line 5361 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 716:
#line 5363 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 717:
#line 5367 "gram1.y"
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

  case 718:
#line 5396 "gram1.y"
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

  case 719:
#line 5419 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 720:
#line 5439 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 721:
#line 5441 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 722:
#line 5445 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 723:
#line 5466 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 724:
#line 5468 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 725:
#line 5471 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 726:
#line 5480 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 727:
#line 5484 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 728:
#line 5489 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 729:
#line 5491 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 730:
#line 5493 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 731:
#line 5495 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 732:
#line 5501 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 733:
#line 5503 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 734:
#line 5507 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 735:
#line 5517 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
    break;

  case 736:
#line 5521 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 737:
#line 5523 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 738:
#line 5528 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 739:
#line 5530 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 740:
#line 5534 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 741:
#line 5538 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 742:
#line 5544 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 743:
#line 5554 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 744:
#line 5556 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 745:
#line 5560 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 746:
#line 5562 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 747:
#line 5564 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 748:
#line 5571 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 749:
#line 5588 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 750:
#line 5590 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 751:
#line 5594 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 752:
#line 5596 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 753:
#line 5600 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 754:
#line 5607 "gram1.y"
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

  case 755:
#line 5617 "gram1.y"
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

  case 756:
#line 5646 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 757:
#line 5661 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 758:
#line 5668 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 759:
#line 5686 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 760:
#line 5688 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 761:
#line 5692 "gram1.y"
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

  case 762:
#line 5706 "gram1.y"
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

  case 763:
#line 5732 "gram1.y"
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

  case 764:
#line 5745 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 765:
#line 5761 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 766:
#line 5763 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 767:
#line 5766 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 768:
#line 5768 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 769:
#line 5774 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 770:
#line 5778 "gram1.y"
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

  case 771:
#line 5806 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 772:
#line 5808 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 773:
#line 5812 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 774:
#line 5820 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 775:
#line 5826 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 776:
#line 5829 "gram1.y"
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

  case 777:
#line 5887 "gram1.y"
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

  case 778:
#line 5951 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 779:
#line 5953 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 780:
#line 5956 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 781:
#line 5960 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 782:
#line 5964 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 783:
#line 5968 "gram1.y"
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 784:
#line 5985 "gram1.y"
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

  case 785:
#line 5997 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 786:
#line 6001 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 787:
#line 6005 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 788:
#line 6015 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 789:
#line 6020 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 790:
#line 6025 "gram1.y"
    {
                 type_opt = COMMON_BIT;
                 (yyval.ll_node) = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                ;}
    break;

  case 791:
#line 6032 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 792:
#line 6040 "gram1.y"
    {ndim = 0;;}
    break;

  case 793:
#line 6041 "gram1.y"
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

  case 794:
#line 6052 "gram1.y"
    { PTR_LLND  q;
             if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		q = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL);
	      ++ndim;
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), q, EXPR_LIST);
            ;}
    break;

  case 795:
#line 6063 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 796:
#line 6065 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 797:
#line 6069 "gram1.y"
    {PTR_SYMB s;
           /* s = make_scalar($1,TYNULL,LOCAL);*/
            s = make_array((yyvsp[(1) - (1)].hash_entry),TYNULL,LLNULL,0,LOCAL);
            s->attr = s->attr | DVM_POINTER_BIT;
            if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT))
               errstr( "Inconsistent declaration of identifier %s", s->ident, 16);     
            (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL,s);
            ;}
    break;

  case 798:
#line 6080 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 799:
#line 6084 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 800:
#line 6086 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 801:
#line 6090 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 802:
#line 6101 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 803:
#line 6105 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 804:
#line 6107 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 805:
#line 6111 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 806:
#line 6123 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 807:
#line 6125 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 808:
#line 6132 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 809:
#line 6134 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 810:
#line 6138 "gram1.y"
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

  case 811:
#line 6154 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 812:
#line 6164 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                 ;}
    break;

  case 813:
#line 6173 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 814:
#line 6175 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 816:
#line 6182 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 817:
#line 6185 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 818:
#line 6190 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
           errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
         ;}
    break;

  case 819:
#line 6200 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 820:
#line 6202 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 821:
#line 6206 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 822:
#line 6208 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 823:
#line 6216 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 824:
#line 6218 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 825:
#line 6222 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 826:
#line 6224 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 837:
#line 6241 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 838:
#line 6246 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 839:
#line 6250 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 840:
#line 6254 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 841:
#line 6258 "gram1.y"
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

  case 842:
#line 6271 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 843:
#line 6275 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 844:
#line 6279 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 845:
#line 6283 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 846:
#line 6286 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 847:
#line 6288 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 848:
#line 6290 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 849:
#line 6294 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 850:
#line 6296 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 851:
#line 6300 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 852:
#line 6305 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 853:
#line 6309 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 854:
#line 6313 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 855:
#line 6315 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 856:
#line 6319 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 857:
#line 6327 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 858:
#line 6333 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 859:
#line 6339 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 860:
#line 6343 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 861:
#line 6345 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 862:
#line 6349 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 863:
#line 6351 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 864:
#line 6355 "gram1.y"
    { /*  PTR_LLND p;
                       p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
                       p->entry.string_val = (char *) "corner";
                       p->type = global_string;
                   */
                   (yyvsp[(1) - (7)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (7)].ll_node);  
                   (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 865:
#line 6367 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 866:
#line 6369 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 867:
#line 6373 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 868:
#line 6377 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 869:
#line 6379 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 870:
#line 6383 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 871:
#line 6385 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 872:
#line 6387 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 873:
#line 6389 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 874:
#line 6391 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 875:
#line 6393 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 876:
#line 6395 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 877:
#line 6399 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 878:
#line 6403 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 879:
#line 6407 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 880:
#line 6411 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 881:
#line 6415 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 882:
#line 6422 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 883:
#line 6428 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 884:
#line 6432 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 885:
#line 6435 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 886:
#line 6439 "gram1.y"
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

  case 887:
#line 6452 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 888:
#line 6454 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 889:
#line 6458 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 890:
#line 6460 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 891:
#line 6465 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 892:
#line 6471 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 893:
#line 6477 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 894:
#line 6483 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 895:
#line 6489 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 896:
#line 6495 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 897:
#line 6501 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 898:
#line 6507 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 899:
#line 6513 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 900:
#line 6522 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 901:
#line 6528 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 902:
#line 6545 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 903:
#line 6553 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 904:
#line 6561 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 905:
#line 6563 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 906:
#line 6565 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 907:
#line 6569 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 908:
#line 6573 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 909:
#line 6575 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 910:
#line 6579 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 911:
#line 6581 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 912:
#line 6589 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 913:
#line 6593 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 914:
#line 6604 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 915:
#line 6608 "gram1.y"
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

  case 916:
#line 6626 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 917:
#line 6628 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 918:
#line 6632 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 919:
#line 6634 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 920:
#line 6638 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 921:
#line 6640 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 922:
#line 6644 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 923:
#line 6648 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 924:
#line 6652 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 925:
#line 6661 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 926:
#line 6665 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 927:
#line 6669 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 928:
#line 6674 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 929:
#line 6678 "gram1.y"
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

  case 930:
#line 6690 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 931:
#line 6692 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 932:
#line 6696 "gram1.y"
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 933:
#line 6701 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 934:
#line 6705 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 935:
#line 6707 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 936:
#line 6711 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 937:
#line 6713 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 938:
#line 6717 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 939:
#line 6722 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 940:
#line 6729 "gram1.y"
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

  case 941:
#line 6752 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 942:
#line 6754 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 943:
#line 6756 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 944:
#line 6758 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 945:
#line 6760 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 946:
#line 6764 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 947:
#line 6775 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 948:
#line 6779 "gram1.y"
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

  case 949:
#line 6794 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 950:
#line 6801 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 951:
#line 6807 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 952:
#line 6809 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 953:
#line 6813 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 954:
#line 6817 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 955:
#line 6825 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 956:
#line 6829 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 957:
#line 6833 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 958:
#line 6841 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 959:
#line 6846 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 960:
#line 6860 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 961:
#line 6862 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 962:
#line 6866 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 963:
#line 6868 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 964:
#line 6877 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 965:
#line 6879 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 966:
#line 6881 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 967:
#line 6883 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 968:
#line 6919 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 969:
#line 6923 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 970:
#line 6927 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 971:
#line 6931 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 972:
#line 6935 "gram1.y"
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

  case 973:
#line 6947 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 974:
#line 6949 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 975:
#line 6953 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 976:
#line 6956 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 977:
#line 6958 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 978:
#line 6962 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 979:
#line 6967 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 980:
#line 6974 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 981:
#line 6977 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 982:
#line 6985 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 983:
#line 6989 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 984:
#line 6993 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 985:
#line 6996 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 986:
#line 7004 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_EXIT_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 987:
#line 7008 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 988:
#line 7012 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 989:
#line 7016 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 990:
#line 7020 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 991:
#line 7024 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 992:
#line 7028 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 993:
#line 7031 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 994:
#line 7033 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 995:
#line 7037 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 996:
#line 7039 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 997:
#line 7041 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 998:
#line 7045 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 999:
#line 7049 "gram1.y"
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

  case 1000:
#line 7061 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1001:
#line 7063 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1002:
#line 7067 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1003:
#line 7069 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1004:
#line 7073 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1005:
#line 7075 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 1006:
#line 7079 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 1007:
#line 7083 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 1008:
#line 7089 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 1009:
#line 7101 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1010:
#line 7103 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1011:
#line 7107 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1012:
#line 7109 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1013:
#line 7113 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1014:
#line 7121 "gram1.y"
    { 
                PTR_LLND q;
                if((yyvsp[(16) - (16)].ll_node))
                  q = make_llnd(fi,ARRAY_OP, (yyvsp[(14) - (16)].ll_node), (yyvsp[(16) - (16)].ll_node), SMNULL);
                else
                  q = (yyvsp[(14) - (16)].ll_node);                  
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_CREATE_DIR,SMNULL,(yyvsp[(3) - (16)].ll_node),(yyvsp[(8) - (16)].ll_node),q); 
              ;}
    break;

  case 1015:
#line 7132 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1016:
#line 7134 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PARALLEL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1017:
#line 7136 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1018:
#line 7140 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_LOAD_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1019:
#line 7144 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1020:
#line 7146 "gram1.y"
    {
                PTR_LLND q;
                q = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),q,LLNULL);
              ;}
    break;

  case 1021:
#line 7154 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_WAIT_DIR,SMNULL,(yyvsp[(3) - (9)].ll_node),(yyvsp[(8) - (9)].ll_node),LLNULL); ;}
    break;

  case 1022:
#line 7158 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TEMPLATE_CREATE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1023:
#line 7161 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 1024:
#line 7163 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 1025:
#line 7167 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TEMPLATE_DELETE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1026:
#line 7171 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 1027:
#line 7173 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 1055:
#line 7206 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1056:
#line 7212 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1057:
#line 7218 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1058:
#line 7224 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1059:
#line 7230 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1060:
#line 7234 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1070:
#line 7251 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1071:
#line 7256 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1072:
#line 7261 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1073:
#line 7267 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1074:
#line 7273 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1075:
#line 7279 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1076:
#line 7284 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1077:
#line 7290 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1078:
#line 7296 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1079:
#line 7302 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1080:
#line 7309 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1081:
#line 7315 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1082:
#line 7321 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1083:
#line 7328 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1085:
#line 7334 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1086:
#line 7340 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1087:
#line 7347 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1088:
#line 7353 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1089:
#line 7359 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1090:
#line 7365 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1091:
#line 7371 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1092:
#line 7377 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1093:
#line 7383 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1094:
#line 7389 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1095:
#line 7395 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1096:
#line 7401 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1097:
#line 7407 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1098:
#line 7413 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1099:
#line 7423 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1100:
#line 7428 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1101:
#line 7434 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1102:
#line 7438 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1107:
#line 7450 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1108:
#line 7458 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1109:
#line 7464 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1110:
#line 7470 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1111:
#line 7475 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1112:
#line 7481 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1113:
#line 7488 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1114:
#line 7494 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1115:
#line 7498 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1122:
#line 7512 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1123:
#line 7521 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1124:
#line 7525 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1125:
#line 7531 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1126:
#line 7538 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1127:
#line 7545 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1128:
#line 7552 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1129:
#line 7561 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1130:
#line 7567 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1131:
#line 7573 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1132:
#line 7577 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1135:
#line 7587 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1136:
#line 7593 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1137:
#line 7599 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1138:
#line 7603 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1141:
#line 7614 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1142:
#line 7620 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1143:
#line 7626 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1144:
#line 7631 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1145:
#line 7639 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1146:
#line 7645 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1147:
#line 7650 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1148:
#line 7657 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1149:
#line 7661 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1161:
#line 7681 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1162:
#line 7686 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1163:
#line 7691 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1164:
#line 7698 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1165:
#line 7703 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1166:
#line 7709 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1167:
#line 7715 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1168:
#line 7720 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1169:
#line 7725 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1170:
#line 7730 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1171:
#line 7734 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1172:
#line 7739 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1173:
#line 7744 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1174:
#line 7748 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1175:
#line 7753 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1176:
#line 7757 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1177:
#line 7763 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1178:
#line 7768 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1179:
#line 7774 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1180:
#line 7779 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1181:
#line 7785 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1182:
#line 7795 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1183:
#line 7799 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1184:
#line 7803 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1185:
#line 7807 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1186:
#line 7812 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1187:
#line 7815 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1194:
#line 7828 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1195:
#line 7832 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1196:
#line 7836 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1197:
#line 7838 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1198:
#line 7840 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1199:
#line 7844 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1200:
#line 7846 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1201:
#line 7848 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1202:
#line 7852 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1203:
#line 7854 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1204:
#line 7858 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1205:
#line 7860 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1206:
#line 7864 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1207:
#line 7867 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1208:
#line 7870 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1209:
#line 7875 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1210:
#line 7877 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1211:
#line 7879 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1212:
#line 7881 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1213:
#line 7883 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1214:
#line 7887 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1215:
#line 7891 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1216:
#line 7896 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1217:
#line 7900 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1218:
#line 7902 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1219:
#line 7906 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1220:
#line 7908 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1221:
#line 7912 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1222:
#line 7916 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1228:
#line 7927 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1229:
#line 7931 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1230:
#line 7935 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1231:
#line 7939 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1232:
#line 7943 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1233:
#line 7947 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1234:
#line 7949 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1237:
#line 7957 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1238:
#line 7961 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1239:
#line 7965 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1240:
#line 7967 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1244:
#line 7977 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1245:
#line 7981 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1246:
#line 7985 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1247:
#line 7989 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1248:
#line 7991 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1249:
#line 7995 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1250:
#line 7997 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_FISSION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1251:
#line 7999 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PRIVATES_EXPANSION_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1252:
#line 8001 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PRIVATES_EXPANSION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1253:
#line 8004 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;


/* Line 1267 of yacc.c.  */
#line 13744 "gram1.tab.c"
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



