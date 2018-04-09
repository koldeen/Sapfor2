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
     BINARY_OP = 337,
     UNARY_OP = 338
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
#define BINARY_OP 337
#define UNARY_OP 338




/* Copy the first part of user declarations.  */
#line 336 "gram1.y"

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
#line 417 "gram1.y"
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
#line 865 "gram1.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 620 "gram1.y"

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
#line 1021 "gram1.tab.c"

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
#define YYLAST   5513

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  339
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  515
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1242
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2442

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   338

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
     332,   333,   334,   335,   336,     1,     2,   337,   338
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
    2141,  2143,  2145,  2149,  2153,  2156,  2160,  2162,  2166,  2168,
    2172,  2174,  2178,  2180,  2185,  2189,  2191,  2195,  2197,  2201,
    2206,  2208,  2213,  2218,  2223,  2227,  2231,  2233,  2237,  2241,
    2243,  2247,  2251,  2253,  2257,  2261,  2263,  2267,  2268,  2274,
    2281,  2290,  2292,  2296,  2298,  2300,  2302,  2307,  2309,  2310,
    2313,  2317,  2320,  2325,  2326,  2328,  2334,  2339,  2346,  2351,
    2353,  2358,  2363,  2365,  2372,  2374,  2378,  2380,  2384,  2386,
    2391,  2393,  2395,  2399,  2401,  2403,  2407,  2409,  2410,  2412,
    2415,  2419,  2421,  2424,  2430,  2435,  2440,  2447,  2449,  2453,
    2455,  2457,  2464,  2469,  2471,  2475,  2477,  2479,  2481,  2483,
    2485,  2489,  2491,  2493,  2495,  2502,  2507,  2509,  2514,  2516,
    2518,  2520,  2522,  2527,  2530,  2538,  2540,  2545,  2547,  2549,
    2561,  2562,  2565,  2569,  2571,  2575,  2577,  2581,  2583,  2587,
    2589,  2593,  2595,  2599,  2601,  2605,  2614,  2616,  2620,  2623,
    2626,  2634,  2636,  2640,  2642,  2646,  2648,  2653,  2655,  2659,
    2661,  2663,  2664,  2666,  2668,  2671,  2673,  2675,  2677,  2679,
    2681,  2683,  2685,  2687,  2689,  2691,  2700,  2707,  2716,  2723,
    2725,  2732,  2739,  2746,  2753,  2755,  2759,  2765,  2767,  2771,
    2780,  2787,  2794,  2799,  2805,  2811,  2814,  2817,  2818,  2820,
    2824,  2826,  2831,  2839,  2841,  2845,  2849,  2851,  2855,  2861,
    2865,  2869,  2871,  2875,  2877,  2879,  2883,  2887,  2891,  2895,
    2906,  2915,  2926,  2927,  2928,  2930,  2933,  2938,  2943,  2950,
    2952,  2954,  2956,  2958,  2960,  2962,  2964,  2966,  2968,  2970,
    2972,  2979,  2984,  2989,  2993,  3003,  3005,  3007,  3011,  3013,
    3019,  3025,  3035,  3036,  3038,  3040,  3044,  3048,  3052,  3056,
    3060,  3067,  3071,  3075,  3079,  3083,  3091,  3097,  3099,  3101,
    3105,  3110,  3112,  3114,  3118,  3120,  3122,  3126,  3130,  3133,
    3137,  3142,  3147,  3153,  3159,  3161,  3164,  3169,  3174,  3179,
    3180,  3182,  3185,  3193,  3200,  3204,  3208,  3216,  3222,  3224,
    3228,  3230,  3235,  3238,  3242,  3246,  3251,  3258,  3262,  3265,
    3269,  3271,  3273,  3278,  3284,  3288,  3295,  3298,  3303,  3306,
    3308,  3312,  3316,  3317,  3319,  3323,  3326,  3329,  3332,  3335,
    3345,  3351,  3353,  3357,  3360,  3363,  3366,  3376,  3381,  3383,
    3387,  3389,  3391,  3394,  3395,  3403,  3405,  3410,  3412,  3416,
    3418,  3420,  3422,  3439,  3440,  3444,  3448,  3452,  3456,  3463,
    3473,  3475,  3477,  3479,  3481,  3483,  3485,  3487,  3489,  3491,
    3493,  3495,  3497,  3499,  3501,  3503,  3505,  3507,  3509,  3511,
    3513,  3515,  3517,  3519,  3521,  3523,  3525,  3527,  3530,  3533,
    3538,  3542,  3547,  3553,  3555,  3557,  3559,  3561,  3563,  3565,
    3567,  3569,  3571,  3577,  3580,  3583,  3586,  3589,  3592,  3598,
    3600,  3602,  3604,  3609,  3614,  3619,  3624,  3626,  3628,  3630,
    3632,  3634,  3636,  3638,  3640,  3642,  3644,  3646,  3648,  3650,
    3652,  3654,  3659,  3663,  3668,  3674,  3676,  3678,  3680,  3682,
    3687,  3691,  3694,  3699,  3703,  3708,  3712,  3717,  3723,  3725,
    3727,  3729,  3731,  3733,  3735,  3737,  3745,  3751,  3753,  3755,
    3757,  3759,  3764,  3768,  3773,  3779,  3781,  3783,  3788,  3792,
    3797,  3803,  3805,  3807,  3810,  3812,  3815,  3820,  3824,  3829,
    3833,  3838,  3844,  3846,  3848,  3850,  3852,  3854,  3856,  3858,
    3860,  3862,  3864,  3866,  3869,  3874,  3878,  3881,  3886,  3890,
    3893,  3897,  3900,  3903,  3906,  3909,  3912,  3915,  3919,  3922,
    3928,  3931,  3937,  3940,  3946,  3948,  3950,  3954,  3958,  3959,
    3960,  3962,  3964,  3966,  3968,  3970,  3972,  3976,  3979,  3985,
    3990,  3993,  3999,  4004,  4007,  4010,  4012,  4014,  4018,  4021,
    4024,  4027,  4032,  4037,  4042,  4047,  4052,  4057,  4059,  4061,
    4063,  4067,  4070,  4073,  4075,  4077,  4079,  4081,  4083,  4085,
    4087,  4092,  4097,  4102,  4105,  4107,  4109,  4113,  4115,  4117,
    4123,  4129,  4131,  4135,  4137,  4139,  4141,  4147,  4153,  4159,
    4161,  4165,  4168
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     340,     0,    -1,    -1,   340,   341,   116,    -1,   342,   343,
     559,    -1,   342,   360,   559,    -1,   342,   505,   559,    -1,
     342,   133,   356,    -1,   342,   247,    -1,   257,    -1,     1,
      -1,   150,    -1,   193,   344,   351,    -1,    57,   344,   352,
      -1,   233,   344,   346,   353,    -1,   345,   233,   344,   346,
     353,    -1,   124,   344,   347,   353,   349,    -1,   348,   353,
     349,    -1,   114,   350,   353,   349,    -1,   164,   344,   350,
      -1,    -1,   202,   357,    -1,   195,   357,    -1,    95,   357,
      -1,   350,    -1,   350,    -1,   381,   124,   344,   350,    -1,
     381,   345,   124,   344,   350,    -1,   345,   124,   344,   350,
      -1,   345,   381,   124,   344,   350,    -1,   357,   358,    -1,
     357,   213,    15,   350,    21,    -1,   129,    -1,    -1,   350,
      -1,    -1,   350,    -1,    -1,    15,    21,    -1,    15,   354,
      21,    -1,   355,    -1,   354,     8,   355,    -1,   350,    -1,
       5,    -1,    64,    -1,    -1,    -1,    -1,   365,    -1,   366,
      -1,   367,    -1,   397,    -1,   393,    -1,   560,    -1,   402,
      -1,   403,    -1,   404,    -1,   462,    -1,   383,    -1,   398,
      -1,   408,    -1,   216,   472,    -1,   216,   472,   473,   439,
      -1,   123,   471,    -1,   183,   472,    15,   445,    21,    -1,
     373,    -1,   374,    -1,   379,    -1,   376,    -1,   378,    -1,
     394,    -1,   395,    -1,   396,    -1,   361,    -1,   449,    -1,
     447,    -1,   375,    -1,   142,   472,    -1,   142,   472,   350,
      -1,   141,   472,    15,   363,    21,    -1,   140,   472,    15,
      26,    21,    -1,   107,   514,    -1,    10,    -1,   362,    -1,
     364,    -1,    17,    -1,    16,    -1,     5,    -1,     9,    -1,
      37,    -1,    23,    -1,    22,    -1,    35,    -1,    38,    -1,
      34,    -1,    25,    -1,    32,    -1,    29,    -1,    28,    -1,
      31,    -1,    30,    -1,    33,    -1,    24,    -1,   245,   472,
     473,   350,    -1,   245,     8,   472,   357,   372,   473,   350,
      -1,   112,   472,    -1,   112,   472,   350,    -1,   381,   368,
     350,   472,   455,   387,   392,    -1,   367,     8,   350,   455,
     387,   392,    -1,    -1,     7,     7,    -1,     8,   357,   369,
       7,     7,    -1,   370,    -1,   369,     8,   357,   370,    -1,
     183,    -1,   372,    -1,    44,    -1,    87,   455,    -1,   119,
      -1,   145,    15,   371,    21,    -1,   143,    -1,   178,    -1,
     187,    -1,   216,    -1,   230,    -1,   236,    -1,   357,   148,
      -1,   357,   180,    -1,   357,   147,    -1,   194,    -1,   191,
      -1,   145,   472,    15,   371,    21,   473,   350,    -1,   373,
       8,   350,    -1,   178,   472,   473,   350,    -1,   374,     8,
     350,    -1,   230,   472,   473,   401,    -1,   375,     8,   401,
      -1,   191,   472,    -1,   191,   472,   473,   377,   441,    -1,
      -1,   219,   472,    -1,   194,   472,    -1,   194,   472,   473,
     380,   441,    -1,    -1,   385,   382,   389,   382,    -1,   244,
      15,   350,    21,   382,    -1,    -1,   384,   350,    -1,   383,
       8,   350,    -1,    13,    -1,     6,    -1,   386,    -1,   144,
      -1,   200,    -1,    68,    -1,    90,    -1,    91,    -1,   154,
      -1,    63,    -1,    -1,   388,    -1,     5,   535,   492,   536,
     382,    -1,     5,   535,    15,   536,     5,    21,    -1,     5,
     535,    15,   536,   478,    21,    -1,    -1,   388,    -1,    15,
     555,   390,   391,    21,    -1,    15,   555,   390,   391,     8,
     555,   390,   391,    21,    -1,   478,    -1,     5,    -1,   546,
     478,    -1,   546,     5,    -1,    -1,    -1,    26,   478,    -1,
      18,   478,    -1,    87,   473,   472,   350,   455,    -1,   393,
       8,   350,   455,    -1,    44,   472,   473,   401,    -1,   394,
       8,   401,    -1,   187,   472,   473,   401,    -1,   395,     8,
     401,    -1,   236,   472,   473,   401,    -1,   396,     8,   401,
      -1,    67,   472,   401,    -1,    67,   472,   400,   401,    -1,
     397,   529,   400,   529,   401,    -1,   397,     8,   401,    -1,
     167,   472,   399,   481,    -1,   398,   529,   399,   529,   481,
      -1,   398,     8,   481,    -1,    37,   350,    37,    -1,    23,
      -1,    37,   350,    37,    -1,   350,   455,    -1,   119,   472,
     473,   350,    -1,   402,     8,   350,    -1,   143,   472,   473,
     350,    -1,   403,     8,   350,    -1,   117,   472,   405,    -1,
     404,     8,   405,    -1,    15,   406,    21,    -1,   407,     8,
     407,    -1,   406,     8,   407,    -1,   350,    -1,   350,    15,
     477,    21,    -1,   486,    -1,   409,    -1,    80,   471,   410,
     412,    -1,   409,   529,   412,    -1,    -1,    -1,   413,    37,
     414,    37,    -1,   415,    -1,   413,     8,   415,    -1,   426,
      -1,   414,     8,   426,    -1,   416,   418,    -1,   416,   418,
     419,    -1,   416,   418,   420,    -1,   416,   418,   419,   420,
      -1,   416,   423,    -1,    -1,   350,    -1,   350,    -1,    15,
     421,    21,    -1,    15,   422,     7,   422,    21,    -1,   435,
      -1,   421,     8,   435,    -1,    -1,   435,    -1,    15,   424,
       8,   417,    26,   421,    21,    -1,   425,    -1,   424,     8,
     425,    -1,   418,   419,    -1,   418,   420,    -1,   418,   419,
     420,    -1,   423,    -1,   427,    -1,   416,   417,     5,   427,
      -1,   430,     5,   427,    -1,   416,   417,    -1,   429,    -1,
     431,    -1,   433,    -1,    36,    -1,    36,   246,   495,    -1,
      27,    -1,    27,   246,   495,    -1,    64,    -1,   428,    -1,
     416,   481,    15,   555,   474,    21,    -1,    59,    -1,   430,
      -1,    17,   430,    -1,    16,   430,    -1,   149,    -1,   149,
     246,   495,    -1,   432,    -1,    17,   432,    -1,    16,   432,
      -1,   201,    -1,   201,   246,   495,    -1,    92,    -1,    92,
     246,   495,    -1,    15,   434,     8,   434,    21,    -1,   431,
      -1,   429,    -1,   436,    -1,    17,   436,    -1,    16,   436,
      -1,   435,    17,   436,    -1,   435,    16,   436,    -1,   437,
      -1,   436,     5,   437,    -1,   436,    37,   437,    -1,   438,
      -1,   438,     9,   437,    -1,   149,    -1,   417,    -1,    15,
     435,    21,    -1,   440,    -1,   439,     8,   440,    -1,   401,
      -1,   400,    -1,   442,   444,   443,    -1,   441,     8,   442,
     444,   443,    -1,    -1,    -1,   350,    -1,   177,    15,   363,
      21,    -1,    47,    15,    26,    21,    -1,   446,    -1,   445,
       8,   446,    -1,   350,    26,   478,    -1,   163,   448,    -1,
     350,    -1,   448,     8,   350,    -1,   248,   472,   450,    -1,
     248,   472,   450,     8,   359,   453,    -1,   248,   472,   450,
       8,   359,   172,    -1,   248,   472,   450,     8,   359,   172,
     451,    -1,   350,    -1,   452,    -1,   451,     8,   452,    -1,
     350,    18,   350,    -1,   350,    -1,   454,    -1,   453,     8,
     454,    -1,   350,    18,   350,    -1,    -1,    15,   456,    21,
      -1,    -1,   457,   458,    -1,   456,     8,   458,    -1,   459,
      -1,     7,    -1,   478,     7,    -1,   478,     7,   459,    -1,
       5,    -1,   478,    -1,   461,    -1,   460,     8,   461,    -1,
     149,    -1,   130,   472,   463,    -1,   131,    -1,   464,    -1,
     463,     8,   464,    -1,   465,    15,   468,    21,    -1,    -1,
     466,   467,    -1,   231,   386,    -1,   381,    -1,   469,    -1,
     468,     8,   469,    -1,   470,    -1,   470,    16,   470,    -1,
     129,    -1,    -1,    -1,    -1,     7,     7,    -1,    -1,   476,
      -1,   478,    -1,   496,    -1,   546,   478,    -1,   555,   475,
      -1,   476,     8,   555,   475,    -1,   478,    -1,   477,     8,
     478,    -1,   479,    -1,    15,   478,    21,    -1,   494,    -1,
     482,    -1,   490,    -1,   497,    -1,   478,    17,   478,    -1,
     478,    16,   478,    -1,   478,     5,   478,    -1,   478,    37,
     478,    -1,   478,     9,   478,    -1,   362,   478,    -1,    17,
     478,    -1,    16,   478,    -1,   478,    25,   478,    -1,   478,
      29,   478,    -1,   478,    31,   478,    -1,   478,    28,   478,
      -1,   478,    30,   478,    -1,   478,    32,   478,    -1,   478,
      24,   478,    -1,   478,    33,   478,    -1,   478,    38,   478,
      -1,   478,    35,   478,    -1,   478,    22,   478,    -1,    34,
     478,    -1,   478,    23,   478,    -1,   478,   362,   478,    -1,
      17,    -1,    16,    -1,   350,    -1,   481,    -1,   484,    -1,
     483,    -1,   481,    15,   555,   474,    21,    -1,   481,    15,
     555,   474,    21,   488,    -1,   484,    15,   474,    21,    -1,
     484,    15,   474,    21,   488,    -1,   482,     3,   129,    -1,
     481,    -1,   484,    -1,   481,    15,   555,   474,    21,    -1,
     484,    15,   474,    21,    -1,   481,   488,    -1,    -1,   488,
      -1,    15,   489,     7,   489,    21,    -1,    -1,   478,    -1,
     491,    -1,   491,   246,   495,    -1,   492,    -1,   492,   246,
     495,    -1,   493,   487,    -1,    36,    -1,    27,    -1,   201,
      -1,    92,    -1,   149,    -1,    64,    -1,   481,   246,    64,
      -1,   492,   246,    64,    -1,    15,   479,     8,   479,    21,
      -1,   481,    -1,   492,    -1,   478,     7,   478,    -1,   478,
       7,    -1,   478,     7,   478,     7,   478,    -1,   478,     7,
       7,   478,    -1,     7,   478,     7,   478,    -1,     7,     7,
     478,    -1,     7,   478,    -1,     7,    -1,    -1,    -1,    14,
     391,   498,   552,   499,    20,    -1,   481,    -1,   484,    -1,
     485,    -1,   501,     8,   555,   485,    -1,   501,     8,   555,
     546,   481,    -1,   500,    -1,   502,     8,   555,   500,    -1,
     502,     8,   555,   546,   481,    -1,    -1,   481,    -1,   504,
       8,   481,    -1,   526,    -1,   525,    -1,   508,    -1,   516,
     508,    -1,   102,   534,   514,    -1,   103,   534,   513,    -1,
     108,   514,    -1,   506,    -1,   516,   506,    -1,   517,   526,
      -1,   517,   239,    -1,   516,   517,   239,    -1,    97,   534,
      15,   478,    21,   239,   513,    -1,    96,   534,   513,    -1,
     106,   534,   513,    -1,   509,    -1,    76,   534,    -1,   518,
     526,    -1,   518,    -1,   516,   518,    -1,   105,   534,   513,
      -1,   561,    -1,   820,    -1,   836,    -1,    89,   534,    15,
     478,    21,    -1,    89,   534,   535,   524,   536,   595,   507,
      -1,    -1,     8,   357,   254,    15,   478,    21,    -1,   254,
      15,   478,    21,    -1,   185,   534,   535,   524,   536,   529,
     522,    26,   478,     8,   478,    -1,   185,   534,   535,   524,
     536,   529,   522,    26,   478,     8,   478,     8,   478,    -1,
      62,   534,   510,   513,    -1,    84,   534,   513,    -1,   110,
     534,   513,    -1,   218,   534,   357,    62,    15,   478,    21,
      -1,   516,   218,   534,   357,    62,    15,   478,    21,    -1,
      15,   512,    21,    -1,   478,    -1,   478,     7,    -1,     7,
     478,    -1,   478,     7,   478,    -1,   511,    -1,   512,     8,
     511,    -1,    -1,   350,    -1,    -1,   350,    -1,    75,    -1,
     515,     7,    -1,   155,   534,    15,   478,    21,    -1,   122,
     534,    15,   519,   521,    21,    -1,   520,    -1,   519,     8,
     520,    -1,   522,    26,   496,    -1,    -1,     8,   478,    -1,
     350,    -1,   522,    26,   478,     8,   478,    -1,   522,    26,
     478,     8,   478,     8,   478,    -1,    -1,   149,    -1,   113,
     534,   513,    -1,    98,   534,   513,    -1,    98,   534,    15,
     478,    21,   513,    -1,   252,   534,    15,   478,    21,    -1,
     516,   252,   534,    15,   478,    21,    -1,   527,   478,    26,
     478,    -1,   188,   534,   482,    18,   478,    -1,    48,   534,
     461,   240,   350,    -1,    77,   534,    -1,   528,    -1,   537,
      -1,    46,   534,    15,   478,    21,   461,     8,   461,     8,
     461,    -1,   530,    -1,   530,    15,    21,    -1,   530,    15,
     531,    21,    -1,   214,   534,   489,    -1,   533,   534,   489,
      -1,    79,   534,   513,    -1,   115,   534,   513,    -1,    45,
     534,    15,   503,   501,    21,    -1,    81,   534,    15,   503,
     502,    21,    -1,   170,   534,    15,   504,    21,    -1,   253,
     534,    15,   478,    21,   482,    26,   478,    -1,   152,   411,
      -1,   186,   534,   461,    -1,    49,   534,   350,    -1,    49,
     534,   350,   529,    15,   460,    21,    -1,    69,   534,    15,
     460,    21,   529,   478,    -1,    -1,     8,    -1,    61,   534,
     350,   555,    -1,   555,   532,    -1,   531,     8,   555,   532,
      -1,   478,    -1,   546,   478,    -1,     5,   461,    -1,   184,
      -1,   232,    -1,    -1,    -1,    -1,   538,   543,    -1,   538,
     558,    -1,   538,     5,    -1,   538,     9,    -1,   540,   543,
      -1,   547,   543,    -1,   547,   542,    -1,   547,   543,   550,
      -1,   547,   542,     8,   550,    -1,   548,   543,    -1,   548,
     543,   552,    -1,   549,    -1,   549,     8,   552,    -1,   539,
     534,   556,    -1,    53,    -1,   215,    -1,   104,    -1,   541,
     534,   556,    -1,   139,    -1,   176,    -1,    66,    -1,   558,
      -1,     5,    -1,    15,   557,    21,    -1,    15,   544,    21,
      -1,   545,    -1,   544,     8,   555,   545,    -1,   557,    -1,
       5,    -1,     9,    -1,   546,   478,    -1,   546,     5,    -1,
     546,     9,    -1,   166,    -1,   197,   534,   556,    -1,   256,
     534,   556,    -1,   190,   534,   557,   556,    -1,   190,   534,
       5,   556,    -1,   551,    -1,   550,     8,   551,    -1,   482,
      -1,    15,   550,     8,   523,    21,    -1,   479,    -1,   554,
      -1,   553,    -1,   479,     8,   479,    -1,   479,     8,   554,
      -1,   554,     8,   479,    -1,   554,     8,   554,    -1,   553,
       8,   479,    -1,   553,     8,   554,    -1,   494,    -1,    15,
     478,    21,    -1,    15,   479,     8,   523,    21,    -1,    15,
     554,     8,   523,    21,    -1,    15,   553,     8,   523,    21,
      -1,    -1,    -1,   558,    -1,    15,   557,    21,    -1,   482,
      -1,   490,    -1,   557,   480,   557,    -1,   557,     5,   557,
      -1,   557,    37,   557,    -1,   557,     9,   557,    -1,   480,
     557,    -1,   557,    23,   557,    -1,   129,    26,   478,    -1,
      -1,   257,    -1,   562,    -1,   610,    -1,   585,    -1,   564,
      -1,   575,    -1,   570,    -1,   622,    -1,   625,    -1,   701,
      -1,   567,    -1,   576,    -1,   578,    -1,   580,    -1,   582,
      -1,   630,    -1,   636,    -1,   633,    -1,   757,    -1,   755,
      -1,   586,    -1,   611,    -1,   640,    -1,   690,    -1,   688,
      -1,   689,    -1,   691,    -1,   692,    -1,   693,    -1,   694,
      -1,   695,    -1,   703,    -1,   705,    -1,   710,    -1,   707,
      -1,   709,    -1,   713,    -1,   711,    -1,   712,    -1,   724,
      -1,   728,    -1,   729,    -1,   732,    -1,   731,    -1,   733,
      -1,   734,    -1,   735,    -1,   736,    -1,   639,    -1,   718,
      -1,   719,    -1,   720,    -1,   723,    -1,   737,    -1,   740,
      -1,   745,    -1,   750,    -1,   752,    -1,   753,    -1,   754,
      -1,   716,    -1,   756,    -1,    82,   472,   563,    -1,   562,
       8,   563,    -1,   350,   455,    -1,    94,   472,   565,    -1,
     566,    -1,   565,     8,   566,    -1,   350,    -1,   138,   472,
     568,    -1,   569,    -1,   568,     8,   569,    -1,   350,    -1,
     228,   472,   574,   571,    -1,    15,   572,    21,    -1,   573,
      -1,   572,     8,   573,    -1,   478,    -1,   478,     7,   478,
      -1,     7,    15,   477,    21,    -1,   350,    -1,   259,   472,
     350,   455,    -1,   303,   472,   350,   455,    -1,   575,     8,
     350,   455,    -1,   136,   472,   577,    -1,   576,     8,   577,
      -1,   350,    -1,   211,   472,   579,    -1,   578,     8,   579,
      -1,   350,    -1,   205,   472,   581,    -1,   580,     8,   581,
      -1,   350,    -1,    70,   472,   583,    -1,   582,     8,   583,
      -1,   350,    -1,   175,   350,   455,    -1,    -1,    88,   472,
     589,   592,   584,    -1,   204,   534,   589,   593,   595,   584,
      -1,   204,   534,   593,   595,   584,     7,     7,   587,    -1,
     588,    -1,   587,     8,   588,    -1,   589,    -1,   590,    -1,
     350,    -1,   350,    15,   477,    21,    -1,   350,    -1,    -1,
     593,   595,    -1,    15,   594,    21,    -1,   595,   596,    -1,
     594,     8,   595,   596,    -1,    -1,    58,    -1,    58,    15,
     555,   609,    21,    -1,   126,    15,   597,    21,    -1,   258,
      15,   597,     8,   478,    21,    -1,   165,    15,   478,    21,
      -1,     5,    -1,   137,    15,   597,    21,    -1,    86,    15,
     598,    21,    -1,   350,    -1,    15,   599,    21,   357,   255,
     601,    -1,   600,    -1,   599,     8,   600,    -1,   478,    -1,
     478,     7,   478,    -1,   602,    -1,   602,    15,   603,    21,
      -1,   350,    -1,   604,    -1,   603,     8,   604,    -1,   478,
      -1,   749,    -1,    40,   605,   606,    -1,   350,    -1,    -1,
     607,    -1,    17,   608,    -1,   606,    17,   608,    -1,   478,
      -1,   546,   478,    -1,   546,   478,     8,   546,   478,    -1,
      43,   472,   613,   615,    -1,   199,   534,   614,   615,    -1,
     199,   534,   615,     7,     7,   612,    -1,   614,    -1,   612,
       8,   614,    -1,   350,    -1,   481,    -1,    15,   620,    21,
     357,   255,   616,    -1,   619,    15,   617,    21,    -1,   618,
      -1,   617,     8,   618,    -1,   478,    -1,     5,    -1,   496,
      -1,   350,    -1,   621,    -1,   620,     8,   621,    -1,   350,
      -1,     5,    -1,     7,    -1,   623,     7,     7,   472,   350,
     455,    -1,   622,     8,   350,   455,    -1,   624,    -1,   623,
       8,   357,   624,    -1,    82,    -1,   259,    -1,   303,    -1,
      94,    -1,    87,    15,   456,    21,    -1,   228,   571,    -1,
      43,    15,   620,    21,   357,   255,   616,    -1,    43,    -1,
      88,   593,   595,   584,    -1,    88,    -1,    67,    -1,   381,
       8,   357,    93,   472,    15,   626,    21,     7,     7,   628,
      -1,    -1,   627,     7,    -1,   626,     8,     7,    -1,   629,
      -1,   628,     8,   629,    -1,   350,    -1,   127,   472,   631,
      -1,   632,    -1,   631,     8,   632,    -1,   350,    -1,    74,
     472,   634,    -1,   635,    -1,   634,     8,   635,    -1,   350,
      -1,    51,   472,   637,    -1,    51,   472,     8,   357,    67,
       7,     7,   637,    -1,   638,    -1,   637,     8,   638,    -1,
     350,   455,    -1,   168,   534,    -1,   182,   534,    15,   641,
      21,   643,   647,    -1,   642,    -1,   641,     8,   642,    -1,
     481,    -1,   595,   173,   644,    -1,   595,    -1,   481,    15,
     645,    21,    -1,   646,    -1,   645,     8,   646,    -1,   478,
      -1,     5,    -1,    -1,   648,    -1,   649,    -1,   648,   649,
      -1,   653,    -1,   673,    -1,   681,    -1,   650,    -1,   658,
      -1,   660,    -1,   659,    -1,   651,    -1,   654,    -1,   655,
      -1,     8,   357,   209,    15,   696,     7,   697,    21,    -1,
       8,   357,   209,    15,   697,    21,    -1,     8,   357,    71,
      15,   652,     7,   697,    21,    -1,     8,   357,    71,    15,
     697,    21,    -1,   350,    -1,     8,   357,   169,    15,   657,
      21,    -1,     8,   357,   282,    15,   657,    21,    -1,     8,
     357,   191,    15,   657,    21,    -1,     8,   357,   320,    15,
     656,    21,    -1,   478,    -1,   478,     8,   478,    -1,   478,
       8,   478,     8,   478,    -1,   482,    -1,   657,     8,   482,
      -1,     8,   357,   135,    15,   696,     7,   714,    21,    -1,
       8,   357,   135,    15,   714,    21,    -1,     8,   357,   229,
      15,   478,    21,    -1,     8,   357,    41,   661,    -1,     8,
     357,    41,   661,   661,    -1,    15,   595,   662,   663,    21,
      -1,   148,     7,    -1,   180,     7,    -1,    -1,   664,    -1,
     663,     8,   664,    -1,   686,    -1,   686,    15,   665,    21,
      -1,   686,    15,   665,    21,    15,   667,    21,    -1,   666,
      -1,   665,     8,   666,    -1,   478,     7,   478,    -1,   668,
      -1,   667,     8,   668,    -1,   669,     7,   670,     7,   671,
      -1,   669,     7,   670,    -1,   669,     7,   671,    -1,   669,
      -1,   670,     7,   671,    -1,   670,    -1,   671,    -1,   357,
     217,   672,    -1,   357,   157,   672,    -1,   357,   128,   672,
      -1,    15,   476,    21,    -1,     8,   357,   208,    15,   674,
     678,   675,     8,   677,    21,    -1,     8,   357,   208,    15,
     674,   678,   675,    21,    -1,     8,   357,   208,    15,   674,
     676,   675,     7,   677,    21,    -1,    -1,    -1,   350,    -1,
     357,   678,    -1,   677,     8,   357,   678,    -1,   679,    15,
     482,    21,    -1,   680,    15,   657,     8,   478,    21,    -1,
     234,    -1,   192,    -1,   162,    -1,   159,    -1,    35,    -1,
      22,    -1,    24,    -1,    33,    -1,   247,    -1,   158,    -1,
     161,    -1,     8,   357,   223,    15,   683,    21,    -1,     8,
     357,   224,   682,    -1,     8,   357,   226,   682,    -1,     8,
     357,   221,    -1,     8,   357,   221,    15,   686,    15,   572,
      21,    21,    -1,   350,    -1,   684,    -1,   683,     8,   684,
      -1,   686,    -1,   686,    15,   685,    78,    21,    -1,   686,
      15,   685,   572,    21,    -1,   686,    15,   685,   572,    21,
      15,   357,    78,    21,    -1,    -1,   481,    -1,   686,    -1,
     687,     8,   686,    -1,   225,   534,   682,    -1,   224,   534,
     682,    -1,   227,   534,   682,    -1,   226,   534,   682,    -1,
     222,   534,   682,    15,   683,    21,    -1,   206,   534,   676,
      -1,   207,   534,   676,    -1,    72,   534,   652,    -1,    73,
     534,   652,    -1,   210,   534,    15,   696,     7,   697,    21,
      -1,   210,   534,    15,   697,    21,    -1,   350,    -1,   698,
      -1,   697,     8,   698,    -1,   686,    15,   699,    21,    -1,
     686,    -1,   700,    -1,   699,     8,   700,    -1,   478,    -1,
       7,    -1,   237,   472,   702,    -1,   701,     8,   702,    -1,
     350,   455,    -1,   238,   534,   704,    -1,   238,   534,   704,
     673,    -1,   238,   534,   704,   651,    -1,   238,   534,   704,
     673,   651,    -1,   238,   534,   704,   651,   673,    -1,   350,
      -1,   111,   534,    -1,   704,    15,   478,    21,    -1,   704,
      15,   496,    21,    -1,   174,   534,   483,   708,    -1,    -1,
     653,    -1,   109,   534,    -1,   160,   534,   706,   357,   175,
     591,   455,    -1,   160,   534,   706,   357,   321,   482,    -1,
     189,   534,   696,    -1,   212,   534,   696,    -1,   135,   534,
      15,   696,     7,   714,    21,    -1,   135,   534,    15,   714,
      21,    -1,   715,    -1,   714,     8,   715,    -1,   686,    -1,
     686,    15,   477,    21,    -1,   134,   534,    -1,   134,   534,
     653,    -1,   134,   534,   717,    -1,   134,   534,   653,   717,
      -1,     8,   357,   208,    15,   657,    21,    -1,    50,   534,
     722,    -1,    99,   534,    -1,    52,   534,   722,    -1,   350,
      -1,   721,    -1,   721,    15,   477,    21,    -1,   120,   534,
     482,    26,   482,    -1,    83,   534,   727,    -1,    83,   534,
     727,    15,   725,    21,    -1,   555,   726,    -1,   725,     8,
     555,   726,    -1,   546,   478,    -1,   149,    -1,   100,   534,
     727,    -1,   146,   534,   730,    -1,    -1,   478,    -1,   336,
     534,   477,    -1,   101,   534,    -1,   241,   534,    -1,   242,
     534,    -1,    56,   534,    -1,    65,   534,   555,    15,   531,
      21,   391,   473,   657,    -1,   322,   534,    15,   738,    21,
      -1,   739,    -1,   738,     8,   739,    -1,   357,   315,    -1,
     357,   318,    -1,   357,   182,    -1,   220,   534,    15,   741,
      26,   608,    21,   595,   744,    -1,   481,    15,   742,    21,
      -1,   743,    -1,   742,     8,   743,    -1,   598,    -1,   749,
      -1,   132,   687,    -1,    -1,   153,   534,    15,   481,    18,
     746,    21,    -1,   481,    -1,   481,    15,   747,    21,    -1,
     748,    -1,   747,     8,   748,    -1,   749,    -1,     7,    -1,
       5,    -1,   329,   534,   478,     8,   357,   334,    15,   657,
      21,     8,   357,   333,    15,   477,    21,   751,    -1,    -1,
       8,   357,   182,    -1,     8,   357,   318,    -1,   330,   534,
     478,    -1,   331,   534,   478,    -1,   331,   534,   478,     8,
     357,   315,    -1,   332,   534,   478,     8,   357,   335,    15,
     481,    21,    -1,   806,    -1,   759,    -1,   758,    -1,   776,
      -1,   779,    -1,   780,    -1,   781,    -1,   782,    -1,   788,
      -1,   791,    -1,   796,    -1,   797,    -1,   798,    -1,   801,
      -1,   802,    -1,   803,    -1,   804,    -1,   805,    -1,   807,
      -1,   808,    -1,   809,    -1,   810,    -1,   811,    -1,   812,
      -1,   813,    -1,   814,    -1,   815,    -1,   268,   534,    -1,
     275,   534,    -1,   291,   534,   595,   760,    -1,   291,   534,
     595,    -1,   529,   595,   761,   595,    -1,   760,   529,   595,
     761,   595,    -1,   763,    -1,   772,    -1,   767,    -1,   768,
      -1,   764,    -1,   765,    -1,   766,    -1,   770,    -1,   771,
      -1,   818,    15,   819,   817,    21,    -1,   191,   762,    -1,
     282,   762,    -1,   285,   762,    -1,   265,   762,    -1,   299,
     762,    -1,    84,    15,   357,   769,    21,    -1,   191,    -1,
     299,    -1,   288,    -1,   304,    15,   478,    21,    -1,   289,
      15,   478,    21,    -1,   208,    15,   773,    21,    -1,   595,
     775,     7,   774,    -1,   657,    -1,    17,    -1,    16,    -1,
       5,    -1,    37,    -1,   162,    -1,   159,    -1,    35,    -1,
      22,    -1,    24,    -1,    33,    -1,   305,    -1,   306,    -1,
     307,    -1,   247,    -1,   297,   534,   595,   777,    -1,   297,
     534,   595,    -1,   529,   595,   778,   595,    -1,   777,   529,
     595,   778,   595,    -1,   763,    -1,   772,    -1,   764,    -1,
     765,    -1,   279,   534,   595,   795,    -1,   279,   534,   595,
      -1,   296,   534,    -1,   269,   534,   595,   783,    -1,   269,
     534,   595,    -1,   272,   534,   595,   795,    -1,   272,   534,
     595,    -1,   529,   595,   784,   595,    -1,   783,   529,   595,
     784,   595,    -1,   763,    -1,   772,    -1,   764,    -1,   765,
      -1,   786,    -1,   785,    -1,   290,    -1,   298,    15,   357,
     787,     8,   478,    21,    -1,   298,    15,   357,   787,    21,
      -1,   230,    -1,    94,    -1,   284,    -1,   295,    -1,   300,
     534,   595,   789,    -1,   300,   534,   595,    -1,   529,   595,
     790,   595,    -1,   789,   529,   595,   790,   595,    -1,   763,
      -1,   764,    -1,   280,   534,   595,   792,    -1,   280,   534,
     595,    -1,   529,   595,   793,   595,    -1,   792,   529,   595,
     793,   595,    -1,   795,    -1,   794,    -1,   266,   762,    -1,
     287,    -1,   302,   534,    -1,   281,   534,   595,   795,    -1,
     281,   534,   595,    -1,   292,   534,   595,   799,    -1,   292,
     534,   595,    -1,   529,   595,   800,   595,    -1,   799,   529,
     595,   800,   595,    -1,   763,    -1,   772,    -1,   767,    -1,
     768,    -1,   764,    -1,   765,    -1,   766,    -1,   770,    -1,
     771,    -1,   786,    -1,   785,    -1,   276,   534,    -1,   293,
     534,   595,   760,    -1,   293,   534,   595,    -1,   277,   534,
      -1,   294,   534,   595,   760,    -1,   294,   534,   595,    -1,
     278,   534,    -1,   301,   472,   762,    -1,   286,   534,    -1,
     273,   534,    -1,   290,   534,    -1,   274,   534,    -1,   264,
     534,    -1,   263,   534,    -1,   283,   534,   762,    -1,   283,
     534,    -1,   267,   534,    15,   481,    21,    -1,   267,   534,
      -1,   271,   534,    15,   481,    21,    -1,   271,   534,    -1,
      37,   350,   818,    37,   819,    -1,   816,    -1,   481,    -1,
     817,     8,   816,    -1,   817,     8,   481,    -1,    -1,    -1,
     821,    -1,   834,    -1,   822,    -1,   835,    -1,   823,    -1,
     824,    -1,   308,   534,   825,    -1,   310,   534,    -1,   312,
     534,    15,   831,    21,    -1,   312,   534,    15,    21,    -1,
     312,   534,    -1,   313,   534,    15,   831,    21,    -1,   313,
     534,    15,    21,    -1,   313,   534,    -1,   357,   358,    -1,
     826,    -1,   827,    -1,   826,     8,   827,    -1,   357,   828,
      -1,   357,   830,    -1,   357,   829,    -1,   147,    15,   831,
      21,    -1,   148,    15,   831,    21,    -1,   180,    15,   831,
      21,    -1,   318,    15,   831,    21,    -1,   319,    15,   831,
      21,    -1,   314,    15,   832,    21,    -1,   315,    -1,   657,
      -1,   833,    -1,   832,     8,   833,    -1,   357,   316,    -1,
     357,   317,    -1,   309,    -1,   311,    -1,   837,    -1,   838,
      -1,   839,    -1,   840,    -1,   841,    -1,   323,    15,   842,
      21,    -1,   324,    15,   846,    21,    -1,   325,    15,   851,
      21,    -1,   327,   853,    -1,   328,    -1,   843,    -1,   842,
       8,   843,    -1,   844,    -1,   845,    -1,   357,   208,    15,
     677,    21,    -1,   357,   191,    15,   657,    21,    -1,   847,
      -1,   846,     8,   847,    -1,   848,    -1,   849,    -1,   850,
      -1,   357,   228,    15,   683,    21,    -1,   357,    41,    15,
     683,    21,    -1,   357,   209,    15,   697,    21,    -1,   852,
      -1,   851,     8,   852,    -1,   357,   326,    -1,   350,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   765,   765,   766,   770,   772,   786,   817,   826,   832,
     852,   861,   877,   889,   899,   906,   912,   917,   922,   946,
     973,   987,   989,   991,   995,  1012,  1026,  1050,  1066,  1080,
    1098,  1100,  1107,  1111,  1112,  1119,  1120,  1128,  1129,  1131,
    1135,  1136,  1140,  1144,  1150,  1160,  1164,  1169,  1176,  1177,
    1178,  1179,  1180,  1181,  1182,  1183,  1184,  1185,  1186,  1187,
    1188,  1189,  1194,  1199,  1206,  1208,  1209,  1210,  1211,  1212,
    1213,  1214,  1215,  1216,  1217,  1218,  1219,  1222,  1226,  1234,
    1242,  1251,  1259,  1263,  1265,  1269,  1271,  1273,  1275,  1277,
    1279,  1281,  1283,  1285,  1287,  1289,  1291,  1293,  1295,  1297,
    1299,  1301,  1303,  1308,  1317,  1327,  1335,  1345,  1366,  1386,
    1387,  1389,  1393,  1395,  1399,  1403,  1405,  1409,  1415,  1419,
    1421,  1425,  1429,  1433,  1437,  1441,  1447,  1451,  1455,  1461,
    1466,  1473,  1484,  1497,  1508,  1521,  1531,  1544,  1549,  1556,
    1559,  1564,  1569,  1576,  1579,  1589,  1603,  1606,  1625,  1652,
    1654,  1666,  1674,  1675,  1676,  1677,  1678,  1679,  1680,  1685,
    1686,  1690,  1692,  1699,  1704,  1705,  1707,  1709,  1722,  1728,
    1734,  1743,  1752,  1765,  1766,  1769,  1773,  1788,  1803,  1821,
    1842,  1862,  1884,  1901,  1919,  1926,  1933,  1940,  1953,  1960,
    1967,  1978,  1982,  1984,  1989,  2007,  2018,  2030,  2042,  2056,
    2062,  2069,  2075,  2081,  2089,  2096,  2112,  2115,  2124,  2126,
    2130,  2134,  2154,  2158,  2160,  2164,  2165,  2168,  2170,  2172,
    2174,  2176,  2179,  2182,  2186,  2192,  2196,  2200,  2202,  2207,
    2208,  2212,  2216,  2218,  2222,  2224,  2226,  2231,  2235,  2237,
    2239,  2242,  2244,  2245,  2246,  2247,  2248,  2249,  2250,  2251,
    2254,  2255,  2261,  2264,  2265,  2267,  2271,  2272,  2275,  2276,
    2278,  2282,  2283,  2284,  2285,  2287,  2290,  2291,  2300,  2302,
    2309,  2316,  2323,  2332,  2334,  2336,  2340,  2342,  2346,  2355,
    2362,  2369,  2371,  2375,  2379,  2385,  2387,  2392,  2396,  2400,
    2407,  2414,  2424,  2426,  2430,  2442,  2445,  2454,  2467,  2473,
    2479,  2485,  2493,  2503,  2505,  2509,  2530,  2555,  2557,  2561,
    2593,  2594,  2598,  2598,  2603,  2607,  2615,  2624,  2633,  2643,
    2649,  2652,  2654,  2658,  2666,  2681,  2688,  2690,  2694,  2710,
    2710,  2714,  2716,  2728,  2730,  2734,  2740,  2752,  2764,  2781,
    2810,  2811,  2819,  2820,  2824,  2826,  2828,  2839,  2843,  2849,
    2851,  2855,  2857,  2859,  2863,  2865,  2869,  2871,  2873,  2875,
    2877,  2879,  2881,  2883,  2885,  2887,  2889,  2891,  2893,  2895,
    2897,  2899,  2901,  2903,  2905,  2907,  2909,  2911,  2913,  2917,
    2918,  2929,  3003,  3015,  3017,  3021,  3152,  3202,  3246,  3288,
    3346,  3348,  3350,  3389,  3432,  3443,  3444,  3448,  3453,  3454,
    3458,  3460,  3466,  3468,  3474,  3484,  3490,  3497,  3503,  3511,
    3519,  3535,  3545,  3558,  3565,  3567,  3590,  3592,  3594,  3596,
    3598,  3600,  3602,  3604,  3608,  3608,  3608,  3622,  3624,  3647,
    3649,  3651,  3667,  3669,  3671,  3685,  3688,  3690,  3698,  3700,
    3702,  3704,  3758,  3778,  3793,  3802,  3805,  3855,  3861,  3866,
    3884,  3886,  3888,  3890,  3892,  3895,  3901,  3903,  3905,  3908,
    3910,  3912,  3939,  3948,  3957,  3958,  3960,  3965,  3972,  3980,
    3982,  3986,  3989,  3991,  3995,  4001,  4003,  4005,  4007,  4011,
    4013,  4022,  4023,  4030,  4031,  4035,  4039,  4060,  4063,  4067,
    4069,  4076,  4081,  4082,  4093,  4110,  4133,  4158,  4159,  4166,
    4168,  4170,  4172,  4174,  4178,  4254,  4266,  4273,  4275,  4276,
    4278,  4287,  4294,  4301,  4309,  4314,  4319,  4322,  4325,  4328,
    4331,  4334,  4338,  4356,  4361,  4380,  4399,  4403,  4404,  4407,
    4411,  4416,  4423,  4425,  4427,  4431,  4432,  4443,  4458,  4462,
    4469,  4472,  4482,  4495,  4508,  4512,  4515,  4518,  4522,  4531,
    4534,  4538,  4540,  4546,  4550,  4552,  4554,  4561,  4565,  4567,
    4569,  4573,  4592,  4608,  4617,  4626,  4628,  4632,  4658,  4673,
    4688,  4705,  4713,  4722,  4730,  4735,  4740,  4762,  4778,  4780,
    4784,  4786,  4793,  4795,  4797,  4801,  4803,  4805,  4807,  4809,
    4811,  4815,  4818,  4821,  4827,  4833,  4842,  4846,  4853,  4855,
    4859,  4861,  4863,  4868,  4873,  4878,  4883,  4892,  4897,  4903,
    4904,  4919,  4920,  4921,  4922,  4923,  4924,  4925,  4926,  4927,
    4928,  4929,  4930,  4931,  4932,  4933,  4934,  4935,  4936,  4937,
    4940,  4941,  4942,  4943,  4944,  4945,  4946,  4947,  4948,  4949,
    4950,  4951,  4952,  4953,  4954,  4955,  4956,  4957,  4958,  4959,
    4960,  4961,  4962,  4963,  4964,  4965,  4966,  4967,  4968,  4969,
    4970,  4971,  4972,  4973,  4974,  4975,  4976,  4977,  4978,  4979,
    4980,  4981,  4985,  4987,  4998,  5018,  5022,  5024,  5028,  5041,
    5045,  5047,  5051,  5062,  5073,  5077,  5079,  5083,  5085,  5087,
    5102,  5114,  5134,  5154,  5176,  5182,  5191,  5199,  5205,  5213,
    5220,  5226,  5235,  5239,  5245,  5253,  5267,  5281,  5286,  5302,
    5317,  5345,  5347,  5351,  5353,  5357,  5386,  5409,  5430,  5431,
    5435,  5456,  5458,  5462,  5470,  5474,  5479,  5481,  5483,  5485,
    5491,  5493,  5497,  5507,  5511,  5513,  5518,  5520,  5524,  5528,
    5534,  5544,  5546,  5550,  5552,  5554,  5561,  5579,  5580,  5584,
    5586,  5590,  5597,  5607,  5636,  5651,  5658,  5676,  5678,  5682,
    5696,  5722,  5735,  5751,  5753,  5756,  5758,  5764,  5768,  5796,
    5798,  5802,  5810,  5816,  5819,  5876,  5940,  5942,  5945,  5949,
    5953,  5957,  5974,  5986,  5990,  5994,  6004,  6009,  6014,  6021,
    6030,  6030,  6041,  6052,  6054,  6058,  6069,  6073,  6075,  6079,
    6090,  6094,  6096,  6100,  6112,  6114,  6121,  6123,  6127,  6143,
    6151,  6162,  6164,  6168,  6171,  6174,  6179,  6189,  6191,  6195,
    6197,  6206,  6207,  6211,  6213,  6218,  6219,  6220,  6221,  6222,
    6223,  6224,  6225,  6226,  6227,  6230,  6235,  6239,  6243,  6247,
    6260,  6264,  6268,  6272,  6275,  6277,  6279,  6283,  6285,  6289,
    6294,  6298,  6302,  6304,  6308,  6316,  6322,  6329,  6332,  6334,
    6338,  6340,  6344,  6356,  6358,  6362,  6366,  6368,  6372,  6374,
    6376,  6378,  6380,  6382,  6384,  6388,  6392,  6396,  6400,  6404,
    6411,  6417,  6422,  6425,  6428,  6441,  6443,  6447,  6449,  6454,
    6460,  6466,  6472,  6478,  6484,  6490,  6496,  6502,  6511,  6517,
    6534,  6536,  6544,  6552,  6554,  6558,  6562,  6564,  6568,  6570,
    6578,  6582,  6594,  6597,  6615,  6617,  6621,  6623,  6627,  6629,
    6633,  6637,  6641,  6650,  6654,  6658,  6663,  6667,  6679,  6681,
    6685,  6690,  6694,  6696,  6700,  6702,  6706,  6711,  6718,  6741,
    6743,  6745,  6747,  6749,  6753,  6764,  6768,  6783,  6790,  6797,
    6798,  6802,  6806,  6814,  6818,  6822,  6830,  6835,  6849,  6851,
    6855,  6857,  6866,  6868,  6870,  6872,  6908,  6912,  6916,  6920,
    6924,  6936,  6938,  6942,  6945,  6947,  6951,  6956,  6963,  6966,
    6974,  6978,  6983,  6985,  6992,  6997,  7001,  7005,  7009,  7013,
    7017,  7020,  7022,  7026,  7028,  7030,  7034,  7038,  7050,  7052,
    7056,  7058,  7062,  7065,  7068,  7072,  7078,  7090,  7092,  7096,
    7098,  7102,  7110,  7122,  7123,  7125,  7129,  7133,  7135,  7143,
    7146,  7148,  7149,  7150,  7151,  7152,  7153,  7154,  7155,  7156,
    7157,  7158,  7159,  7160,  7161,  7162,  7163,  7164,  7165,  7166,
    7167,  7168,  7169,  7170,  7171,  7172,  7173,  7176,  7182,  7188,
    7194,  7200,  7204,  7210,  7211,  7212,  7213,  7214,  7215,  7216,
    7217,  7218,  7221,  7226,  7231,  7237,  7243,  7249,  7254,  7260,
    7266,  7272,  7279,  7285,  7291,  7298,  7302,  7304,  7310,  7317,
    7323,  7329,  7335,  7341,  7347,  7353,  7359,  7365,  7371,  7377,
    7383,  7393,  7398,  7404,  7408,  7414,  7415,  7416,  7417,  7420,
    7428,  7434,  7440,  7445,  7451,  7458,  7464,  7468,  7474,  7475,
    7476,  7477,  7478,  7479,  7482,  7491,  7495,  7501,  7508,  7515,
    7522,  7531,  7537,  7543,  7547,  7553,  7554,  7557,  7563,  7569,
    7573,  7580,  7581,  7584,  7590,  7596,  7601,  7609,  7615,  7620,
    7627,  7631,  7637,  7638,  7639,  7640,  7641,  7642,  7643,  7644,
    7645,  7646,  7647,  7651,  7656,  7661,  7668,  7673,  7679,  7685,
    7690,  7695,  7700,  7704,  7709,  7714,  7718,  7723,  7727,  7733,
    7738,  7744,  7749,  7755,  7765,  7769,  7773,  7777,  7783,  7786,
    7790,  7791,  7792,  7793,  7794,  7795,  7798,  7802,  7806,  7808,
    7810,  7814,  7816,  7818,  7822,  7824,  7828,  7830,  7834,  7837,
    7840,  7845,  7847,  7849,  7851,  7853,  7857,  7861,  7866,  7870,
    7872,  7876,  7878,  7882,  7886,  7890,  7891,  7892,  7893,  7894,
    7897,  7901,  7905,  7909,  7913,  7917,  7919,  7923,  7924,  7927,
    7931,  7935,  7937,  7941,  7942,  7943,  7947,  7951,  7955,  7959,
    7961,  7965,  7969
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
       0,   335,   336,     1,     2,     3,     4,     5,     6,     7,
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
     328,   329,   330,   331,   332,   333,   334,   337,   338
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   339,   340,   340,   341,   341,   341,   341,   341,   341,
     341,   342,   343,   343,   343,   343,   343,   343,   343,   343,
     344,   345,   345,   345,   346,   347,   348,   348,   348,   348,
     349,   349,   350,   351,   351,   352,   352,   353,   353,   353,
     354,   354,   355,   355,   356,   357,   358,   359,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   361,   361,   361,
     361,   361,   362,   363,   363,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   365,   365,   366,   366,   367,   367,   368,
     368,   368,   369,   369,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   371,   371,   371,   372,
     372,   373,   373,   374,   374,   375,   375,   376,   376,   377,
     378,   379,   379,   380,   381,   381,   382,   383,   383,   384,
     384,   385,   386,   386,   386,   386,   386,   386,   386,   387,
     387,   388,   388,   388,   389,   389,   389,   389,   390,   390,
     390,   390,   391,   392,   392,   392,   393,   393,   394,   394,
     395,   395,   396,   396,   397,   397,   397,   397,   398,   398,
     398,   399,   400,   400,   401,   402,   402,   403,   403,   404,
     404,   405,   406,   406,   407,   407,   407,   408,   409,   409,
     410,   411,   412,   413,   413,   414,   414,   415,   415,   415,
     415,   415,   416,   417,   418,   419,   420,   421,   421,   422,
     422,   423,   424,   424,   425,   425,   425,   425,   426,   426,
     426,   427,   427,   427,   427,   427,   427,   427,   427,   427,
     427,   427,   428,   429,   429,   429,   430,   430,   431,   431,
     431,   432,   432,   432,   432,   433,   434,   434,   435,   435,
     435,   435,   435,   436,   436,   436,   437,   437,   438,   438,
     438,   439,   439,   440,   440,   441,   441,   442,   443,   444,
     444,   444,   445,   445,   446,   447,   448,   448,   449,   449,
     449,   449,   450,   451,   451,   452,   452,   453,   453,   454,
     455,   455,   457,   456,   456,   458,   458,   458,   458,   459,
     459,   460,   460,   461,   462,   462,   463,   463,   464,   466,
     465,   467,   467,   468,   468,   469,   469,   470,   471,   472,
     473,   473,   474,   474,   475,   475,   475,   476,   476,   477,
     477,   478,   478,   478,   479,   479,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   479,   479,   479,   480,
     480,   481,   482,   482,   482,   483,   483,   483,   483,   484,
     485,   485,   485,   485,   486,   487,   487,   488,   489,   489,
     490,   490,   490,   490,   490,   491,   491,   491,   491,   492,
     493,   493,   493,   494,   495,   495,   496,   496,   496,   496,
     496,   496,   496,   496,   498,   499,   497,   500,   500,   501,
     501,   501,   502,   502,   502,   503,   504,   504,   505,   505,
     505,   505,   505,   505,   505,   505,   505,   505,   505,   505,
     505,   505,   505,   505,   505,   505,   505,   505,   505,   505,
     505,   505,   506,   506,   507,   507,   507,   508,   508,   509,
     509,   509,   509,   509,   510,   511,   511,   511,   511,   512,
     512,   513,   513,   514,   514,   515,   516,   517,   518,   519,
     519,   520,   521,   521,   522,   523,   523,   524,   524,   525,
     525,   525,   525,   525,   526,   526,   526,   526,   526,   526,
     526,   526,   526,   526,   526,   526,   526,   526,   526,   526,
     526,   526,   527,   528,   528,   528,   528,   529,   529,   530,
     531,   531,   532,   532,   532,   533,   533,   534,   535,   536,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   538,   539,   539,   539,   540,   541,   541,
     541,   542,   542,   543,   543,   544,   544,   545,   545,   545,
     545,   545,   545,   546,   547,   548,   549,   549,   550,   550,
     551,   551,   552,   552,   552,   553,   553,   553,   553,   553,
     553,   554,   554,   554,   554,   554,   555,   556,   557,   557,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   559,
     559,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   562,   562,   563,   564,   565,   565,   566,   567,
     568,   568,   569,   570,   571,   572,   572,   573,   573,   573,
     574,   575,   575,   575,   576,   576,   577,   578,   578,   579,
     580,   580,   581,   582,   582,   583,   584,   584,   585,   586,
     586,   587,   587,   588,   588,   589,   590,   591,   592,   592,
     593,   594,   594,   595,   596,   596,   596,   596,   596,   596,
     596,   596,   597,   598,   599,   599,   600,   600,   601,   601,
     602,   603,   603,   604,   604,   604,   605,   606,   606,   607,
     607,   608,   609,   609,   610,   611,   611,   612,   612,   613,
     614,   615,   616,   617,   617,   618,   618,   618,   619,   620,
     620,   621,   621,   621,   622,   622,   623,   623,   624,   624,
     624,   624,   624,   624,   624,   624,   624,   624,   624,   625,
     627,   626,   626,   628,   628,   629,   630,   631,   631,   632,
     633,   634,   634,   635,   636,   636,   637,   637,   638,   639,
     640,   641,   641,   642,   643,   643,   644,   645,   645,   646,
     646,   647,   647,   648,   648,   649,   649,   649,   649,   649,
     649,   649,   649,   649,   649,   650,   650,   651,   651,   652,
     653,   653,   654,   655,   656,   656,   656,   657,   657,   658,
     658,   659,   660,   660,   661,   662,   662,   662,   663,   663,
     664,   664,   664,   665,   665,   666,   667,   667,   668,   668,
     668,   668,   668,   668,   668,   669,   670,   671,   672,   673,
     673,   673,   674,   675,   676,   677,   677,   678,   678,   679,
     679,   679,   679,   679,   679,   679,   679,   679,   680,   680,
     681,   681,   681,   681,   681,   682,   683,   683,   684,   684,
     684,   684,   685,   686,   687,   687,   688,   688,   689,   689,
     690,   691,   692,   693,   694,   695,   695,   696,   697,   697,
     698,   698,   699,   699,   700,   700,   701,   701,   702,   703,
     703,   703,   703,   703,   704,   705,   706,   706,   707,   708,
     708,   709,   710,   710,   711,   712,   713,   713,   714,   714,
     715,   715,   716,   716,   716,   716,   717,   718,   719,   720,
     721,   722,   722,   723,   724,   724,   725,   725,   726,   727,
     728,   729,   730,   730,   731,   732,   733,   734,   735,   736,
     737,   738,   738,   739,   739,   739,   740,   741,   742,   742,
     743,   743,   744,   744,   745,   746,   746,   747,   747,   748,
     748,   749,   750,   751,   751,   751,   752,   753,   753,   754,
     755,   756,   756,   756,   756,   756,   756,   756,   756,   756,
     756,   756,   756,   756,   756,   756,   756,   756,   756,   756,
     756,   756,   756,   756,   756,   756,   756,   757,   758,   759,
     759,   760,   760,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   762,   763,   764,   765,   766,   767,   768,   769,
     769,   769,   770,   771,   772,   773,   774,   775,   775,   775,
     775,   775,   775,   775,   775,   775,   775,   775,   775,   775,
     775,   776,   776,   777,   777,   778,   778,   778,   778,   779,
     779,   780,   781,   781,   782,   782,   783,   783,   784,   784,
     784,   784,   784,   784,   785,   786,   786,   787,   787,   787,
     787,   788,   788,   789,   789,   790,   790,   791,   791,   792,
     792,   793,   793,   794,   795,   796,   797,   797,   798,   798,
     799,   799,   800,   800,   800,   800,   800,   800,   800,   800,
     800,   800,   800,   801,   802,   802,   803,   804,   804,   805,
     806,   807,   808,   809,   810,   811,   812,   813,   813,   814,
     814,   815,   815,   816,   817,   817,   817,   817,   818,   819,
     820,   820,   820,   820,   820,   820,   821,   822,   823,   823,
     823,   824,   824,   824,   825,   825,   826,   826,   827,   827,
     827,   828,   828,   828,   828,   828,   829,   830,   831,   832,
     832,   833,   833,   834,   835,   836,   836,   836,   836,   836,
     837,   838,   839,   840,   841,   842,   842,   843,   843,   844,
     845,   846,   846,   847,   847,   847,   848,   849,   850,   851,
     851,   852,   853
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
       1,     1,     3,     3,     2,     3,     1,     3,     1,     3,
       1,     3,     1,     4,     3,     1,     3,     1,     3,     4,
       1,     4,     4,     4,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     0,     5,     6,
       8,     1,     3,     1,     1,     1,     4,     1,     0,     2,
       3,     2,     4,     0,     1,     5,     4,     6,     4,     1,
       4,     4,     1,     6,     1,     3,     1,     3,     1,     4,
       1,     1,     3,     1,     1,     3,     1,     0,     1,     2,
       3,     1,     2,     5,     4,     4,     6,     1,     3,     1,
       1,     6,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     6,     4,     1,     4,     1,     1,
       1,     1,     4,     2,     7,     1,     4,     1,     1,    11,
       0,     2,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     8,     1,     3,     2,     2,
       7,     1,     3,     1,     3,     1,     4,     1,     3,     1,
       1,     0,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     8,     6,     8,     6,     1,
       6,     6,     6,     6,     1,     3,     5,     1,     3,     8,
       6,     6,     4,     5,     5,     2,     2,     0,     1,     3,
       1,     4,     7,     1,     3,     3,     1,     3,     5,     3,
       3,     1,     3,     1,     1,     3,     3,     3,     3,    10,
       8,    10,     0,     0,     1,     2,     4,     4,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       6,     4,     4,     3,     9,     1,     1,     3,     1,     5,
       5,     9,     0,     1,     1,     3,     3,     3,     3,     3,
       6,     3,     3,     3,     3,     7,     5,     1,     1,     3,
       4,     1,     1,     3,     1,     1,     3,     3,     2,     3,
       4,     4,     5,     5,     1,     2,     4,     4,     4,     0,
       1,     2,     7,     6,     3,     3,     7,     5,     1,     3,
       1,     4,     2,     3,     3,     4,     6,     3,     2,     3,
       1,     1,     4,     5,     3,     6,     2,     4,     2,     1,
       3,     3,     0,     1,     3,     2,     2,     2,     2,     9,
       5,     1,     3,     2,     2,     2,     9,     4,     1,     3,
       1,     1,     2,     0,     7,     1,     4,     1,     3,     1,
       1,     1,    16,     0,     3,     3,     3,     3,     6,     9,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     4,
       3,     4,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     2,     2,     2,     2,     2,     5,     1,
       1,     1,     4,     4,     4,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     4,     5,     1,     1,     1,     1,     4,
       3,     2,     4,     3,     4,     3,     4,     5,     1,     1,
       1,     1,     1,     1,     1,     7,     5,     1,     1,     1,
       1,     4,     3,     4,     5,     1,     1,     4,     3,     4,
       5,     1,     1,     2,     1,     2,     4,     3,     4,     3,
       4,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     4,     3,     2,     4,     3,     2,
       3,     2,     2,     2,     2,     2,     2,     3,     2,     5,
       2,     5,     2,     5,     1,     1,     3,     3,     0,     0,
       1,     1,     1,     1,     1,     1,     3,     2,     5,     4,
       2,     5,     4,     2,     2,     1,     1,     3,     2,     2,
       2,     4,     4,     4,     4,     4,     4,     1,     1,     1,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     2,     1,     1,     3,     1,     1,     5,
       5,     1,     3,     1,     1,     1,     5,     5,     5,     1,
       3,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,    10,    11,     9,     0,     0,     3,   150,
     149,   785,   339,   537,   537,   537,   537,   537,   339,   537,
     554,   537,    20,   537,   537,   158,   537,   560,   339,   154,
     537,   339,   537,   537,   339,   485,   537,   537,   537,   338,
     537,   778,   537,   537,   340,   787,   537,   155,   156,   781,
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
       0,   339,     8,   339,   537,   537,   537,   779,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   339,   537,   780,   537,  1213,   537,
    1214,   537,   537,   537,     0,     0,     0,     0,  1224,   537,
     537,   537,   537,   537,   609,     0,    37,   609,    73,    48,
      49,    50,    65,    66,    76,    68,    69,    67,   109,    58,
       0,   146,   151,    52,    70,    71,    72,    51,    59,    54,
      55,    56,    60,   207,    75,    74,    57,   609,   445,   440,
     453,     0,     0,     0,   456,   439,   438,     0,   508,   511,
     537,   509,     0,   537,     0,   537,     0,     0,   551,    53,
     459,   611,   614,   620,   616,   615,   621,   622,   623,   624,
     613,   630,   612,   631,   617,     0,   776,   618,   625,   627,
     626,   658,   632,   634,   635,   633,   636,   637,   638,   639,
     640,   619,   641,   642,   644,   645,   643,   647,   648,   646,
     670,   659,   660,   661,   662,   649,   650,   651,   653,   652,
     654,   655,   656,   657,   663,   664,   665,   666,   667,   668,
     669,   629,   671,   628,  1022,  1021,  1023,  1024,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,
    1037,  1020,  1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,
    1046,   460,  1180,  1182,  1184,  1185,  1181,  1183,   461,  1215,
    1216,  1217,  1218,  1219,     0,     0,   340,     0,     0,     0,
       0,     0,     0,     0,   988,    35,     0,     0,   596,     0,
       0,     0,     0,     0,     0,   454,   507,   481,   210,     0,
       0,     0,   481,     0,   312,   339,   723,     0,   723,   538,
       0,    23,   481,     0,   481,   968,     0,   985,   483,   481,
     481,   481,    32,   484,    81,   444,   951,   481,   945,   105,
     481,    37,   481,     0,   340,     0,     0,    63,     0,     0,
     329,    44,     7,   962,     0,     0,     0,     0,     0,    77,
     340,     0,   982,   522,     0,     0,     0,   296,   295,     0,
       0,   809,     0,     0,   340,     0,     0,   538,     0,   340,
       0,     0,     0,   340,    33,   340,    22,   597,     0,    21,
       0,     0,     0,     0,     0,     0,     0,   398,   340,    45,
     140,     0,     0,     0,     0,     0,     0,     0,     0,   783,
     340,     0,   340,     0,     0,   986,   987,     0,   339,   340,
       0,     0,     0,   597,     0,  1166,  1165,  1170,  1047,   723,
    1172,   723,  1162,  1164,  1048,  1153,  1156,  1159,   723,   723,
     723,  1168,  1161,  1163,   723,   723,   723,   723,  1101,   723,
     723,  1178,  1135,     0,    45,  1187,  1190,  1193,     0,    45,
      45,    45,  1242,  1223,     0,     0,     0,     0,     0,   610,
       4,    20,    20,     0,     0,    45,     5,     0,     0,     0,
       0,     0,    45,    20,     0,     0,     0,   147,   164,     0,
       0,     0,     0,   528,     0,   528,     0,     0,     0,     0,
     528,   222,     6,   486,   537,   537,   446,   441,     0,   457,
     448,   447,   455,    82,   172,     0,     0,     0,   406,     0,
     405,   410,   408,   409,   407,   381,     0,     0,   351,   382,
     354,   384,   383,   355,   400,   402,   395,   353,   356,   596,
     398,   542,   543,     0,   380,   379,    32,     0,   600,   601,
     540,     0,   598,   597,     0,   544,   597,   562,   546,   545,
     598,   549,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,   772,   773,   771,     0,   769,   759,     0,
       0,   435,     0,   323,     0,   524,   970,   971,   967,    45,
     310,   804,   806,   969,    36,    13,   596,     0,   481,     0,
     192,     0,   310,     0,   184,     0,   705,   703,   839,   923,
     924,   803,   800,   801,   482,   516,   222,   435,   310,   672,
     979,   974,   470,   341,     0,     0,     0,     0,     0,   715,
     718,   707,     0,   497,   678,   675,   676,   451,     0,     0,
     500,   980,   442,   443,   458,   452,   471,   106,   499,    45,
     517,     0,   199,     0,   382,     0,     0,    37,    25,   799,
     796,   797,   324,   326,     0,     0,    45,   963,   964,     0,
     696,   694,   682,   679,   680,     0,     0,    78,     0,    45,
     983,   981,     0,     0,   944,     0,    45,     0,    19,     0,
       0,     0,     0,   949,     0,     0,     0,   497,   523,     0,
       0,   927,   954,   597,     0,   597,   598,   139,    34,    12,
     143,   574,     0,   760,     0,     0,     0,   723,   702,   700,
     884,   921,   922,     0,   699,   697,   955,   399,   514,     0,
       0,     0,   905,     0,   917,   916,   919,   918,     0,   687,
       0,   685,   690,     0,     0,    37,    24,     0,   310,   936,
     939,     0,    45,     0,   302,   298,     0,     0,   575,   310,
       0,   527,     0,  1105,  1100,   527,  1137,  1167,     0,   527,
     527,   527,   527,   527,   527,  1160,   310,    46,  1186,  1195,
    1196,     0,     0,    45,     0,     0,  1225,  1227,  1228,     0,
       0,  1231,  1233,  1234,  1235,     0,     0,  1239,     0,  1016,
    1017,     0,   984,   349,     0,     0,    20,    43,    38,    42,
       0,    40,    17,    46,   310,   132,   134,   136,   110,     0,
       0,    20,   339,   148,   538,   596,   165,   146,   310,   179,
     181,   183,   187,   527,   190,   527,   196,   198,   200,   209,
       0,   213,     0,    45,     0,   449,   424,     0,   351,   364,
     363,   376,   362,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   596,     0,     0,   596,     0,     0,   398,   404,
     396,   512,     0,     0,   515,   568,   569,   573,     0,   565,
       0,   567,     0,   606,     0,     0,     0,     0,     0,   553,
     567,   557,     0,     0,   580,   547,   578,     0,     0,   351,
     353,   550,   584,   583,   552,   673,   310,   695,   698,   701,
     704,   310,   339,     0,   937,     0,    45,   754,   178,     0,
       0,     0,     0,     0,     0,   312,   808,     0,   529,     0,
     475,   479,     0,   469,   596,     0,   194,   185,     0,   321,
       0,   208,     0,   674,   596,     0,   782,   319,   316,   313,
     315,   320,   310,   723,   720,   729,   724,     0,     0,     0,
       0,     0,   721,   707,   723,     0,   786,     0,   498,   539,
       0,     0,     0,    18,   204,     0,     0,     0,   206,   195,
       0,   494,   492,   489,     0,    45,     0,   329,     0,     0,
     332,   330,     0,    45,   965,   381,   913,   960,     0,     0,
     958,     0,     0,    87,    88,    86,    85,    91,    90,   102,
      95,    98,    97,   100,    99,    96,   101,    94,    92,    89,
      93,    83,     0,    84,   197,     0,     0,     0,     0,     0,
       0,   297,     0,   188,   436,     0,    45,   950,   948,   133,
     813,     0,   811,     0,     0,   292,   539,   180,     0,   577,
       0,   576,   287,   287,     0,   755,     0,   723,   707,   931,
       0,     0,   928,   284,   283,    62,   281,     0,     0,     0,
       0,     0,     0,     0,   684,   683,   135,    14,   182,   938,
      45,   941,   940,   146,     0,   103,    47,     0,     0,   691,
       0,   723,   527,     0,  1134,  1104,  1099,   723,   527,  1136,
    1179,   723,   527,   723,   527,   527,   527,   723,   527,   723,
     527,   692,     0,     0,     0,     0,  1207,     0,     0,  1194,
    1198,  1200,  1199,    45,  1189,   847,  1208,     0,  1192,     0,
       0,     0,   991,     0,     0,    45,  1220,     0,     0,     0,
      45,  1221,  1241,    45,  1222,    45,    45,    45,     0,    28,
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
       0,     0,     0,     0,   693,   775,     0,   785,   788,   778,
       0,   787,   781,     0,   779,   780,   777,   770,     0,   390,
     391,   429,     0,     0,   506,     0,     0,     0,     0,   807,
     477,   476,     0,   474,     0,   193,     0,   527,   802,   427,
     428,   432,     0,     0,     0,   314,   317,   176,     0,   596,
       0,     0,     0,     0,     0,   708,   719,   310,   462,   723,
     677,     0,   481,     0,     0,   201,     0,   394,   973,     0,
       0,     0,    16,   798,   327,   337,     0,   333,   335,   331,
       0,     0,     0,     0,     0,     0,     0,   957,   681,    80,
      79,   128,   126,   127,   340,     0,   487,   423,     0,     0,
       0,     0,   191,     0,   520,     0,     0,   723,     0,     0,
      64,   527,   505,   599,   138,     0,   142,    45,     0,   707,
       0,     0,     0,     0,   926,     0,     0,     0,     0,     0,
     906,   908,     0,   688,   686,     0,    45,   943,    45,   942,
     145,   340,     0,   502,     0,  1169,     0,   723,  1171,     0,
     723,     0,     0,   723,     0,   723,     0,   723,     0,   723,
       0,     0,     0,    45,     0,     0,     0,  1197,     0,  1188,
    1191,   995,   993,   994,    45,   990,     0,    45,  1226,     0,
       0,     0,  1232,  1240,     0,     0,     0,   350,    15,    29,
      41,     0,   173,   160,   117,     0,    45,     0,    45,    27,
     159,   539,   539,   169,   172,   168,     0,   186,   189,   214,
       0,     0,     0,   247,   245,   252,   249,   263,   256,   261,
       0,     0,   215,   238,   250,   242,   253,   243,   258,   244,
       0,   237,     0,   232,   229,   218,   219,     0,     0,   425,
     351,     0,   387,   596,   347,   344,   345,     0,   398,     0,
     534,   533,     0,     0,   579,   352,     0,     0,     0,   351,
     586,   351,   590,   351,   588,   310,     0,   596,   596,   596,
     518,     0,     0,   972,     0,   311,   478,   480,   172,   322,
       0,   596,   519,     0,   976,   596,   975,   318,   320,   722,
       0,     0,     0,   732,     0,     0,     0,     0,   706,   464,
     481,   501,     0,   203,   202,   381,   493,   490,   488,     0,
     491,     0,   328,     0,     0,     0,     0,     0,     0,   959,
       0,  1005,     0,     0,   422,   417,   946,   947,   717,   310,
     953,   437,   812,   815,   821,   294,   293,     0,   287,     0,
       0,   289,   288,     0,   756,   757,   709,     0,   935,   934,
       0,   932,     0,   929,   282,     0,  1011,  1000,     0,   998,
    1001,   751,     0,     0,   920,   912,   689,     0,     0,     0,
       0,     0,   300,     0,   299,   307,     0,  1178,     0,  1178,
    1178,  1114,     0,  1108,  1110,  1111,  1109,   723,  1113,  1112,
       0,  1178,   723,  1132,  1131,     0,     0,  1175,  1174,     0,
       0,  1178,     0,  1178,     0,   723,  1053,  1057,  1058,  1059,
    1055,  1056,  1060,  1061,  1054,     0,  1142,  1146,  1147,  1148,
    1144,  1145,  1149,  1150,  1143,  1152,  1151,   723,     0,  1095,
    1097,  1098,  1096,   723,     0,  1125,  1126,   723,     0,     0,
       0,     0,     0,     0,  1209,     0,     0,   848,   992,     0,
       0,     0,     0,     0,     0,     0,  1018,     0,     0,     0,
       0,   108,   790,     0,   111,     0,   173,     0,   146,     0,
     171,   170,   267,   253,   266,     0,   255,   260,   254,   259,
       0,     0,     0,     0,     0,   222,   212,   223,   241,     0,
     222,   234,   235,     0,     0,     0,     0,   278,   223,   279,
       0,     0,   227,   268,   273,   276,   229,   220,     0,   503,
       0,   413,   385,   388,     0,   346,     0,   531,   566,   567,
       0,     0,   351,     0,     0,     0,   774,   768,   784,     0,
     596,     0,     0,     0,   525,     0,   340,   526,     0,   978,
       0,     0,     0,   736,     0,   734,   731,   726,   730,   728,
       0,    45,     0,   463,   450,   205,   334,   336,     0,     0,
       0,   961,   956,   131,     0,  1004,   421,     0,     0,   416,
     952,     0,    45,   810,   822,   823,   828,   832,   825,   833,
     834,   829,   831,   830,   826,   827,     0,     0,     0,     0,
     285,     0,     0,     0,     0,   930,   925,   472,     0,   997,
     723,   907,     0,     0,   882,   104,   306,   301,   303,     0,
       0,     0,  1063,   723,  1064,  1065,    45,  1106,   723,  1133,
    1129,   723,  1178,     0,  1062,    45,  1066,     0,  1067,     0,
    1051,   723,  1140,   723,  1093,   723,  1123,   723,  1201,  1202,
    1203,  1211,  1212,    45,  1206,  1204,  1205,  1230,   894,   895,
     896,   893,   898,   892,   899,   891,   890,   889,   897,   885,
       0,     0,    45,  1229,  1237,  1238,  1236,     0,     0,    31,
     175,   174,     0,     0,   119,   113,   107,     0,     0,   161,
     596,   166,     0,   248,   246,   264,   257,   262,   216,   222,
     596,     0,   240,   236,   223,     0,   233,     0,   270,   269,
       0,   225,   229,     0,     0,     0,     0,     0,   230,     0,
     426,   386,   348,   397,     0,   581,   593,   595,   594,     0,
       0,   393,   430,     0,     0,   805,     0,   433,     0,   977,
     752,   725,     0,     0,    45,     0,     0,     0,   840,   966,
     841,  1010,     0,  1007,  1009,   420,   419,     0,     0,   814,
       0,   824,     0,   288,     0,     0,   761,   758,   715,   710,
     711,   713,   714,   933,   999,  1003,     0,     0,   381,     0,
       0,     0,     0,     0,   309,   308,   521,     0,     0,     0,
    1107,  1130,     0,  1177,  1176,     0,     0,     0,  1052,  1141,
    1094,  1124,  1210,     0,     0,     0,     0,     0,     0,     0,
     791,   162,   163,     0,     0,   239,   596,   241,     0,   280,
     228,     0,   272,   271,   274,   275,   277,   473,     0,   766,
     765,   767,     0,   763,   392,   431,     0,   989,   434,     0,
     737,   735,     0,   727,     0,     0,     0,  1006,   418,     0,
       0,     0,     0,     0,   903,     0,     0,     0,     0,     0,
       0,   286,   291,   290,     0,     0,     0,   996,   909,   910,
       0,   838,   883,   883,   305,   304,  1079,  1078,  1077,  1084,
    1085,  1086,  1083,  1080,  1082,  1081,  1090,  1087,  1088,  1089,
       0,  1074,  1118,  1117,  1119,  1120,     0,  1179,  1069,  1071,
    1070,     0,  1073,  1072,     0,     0,   886,     0,  1019,   792,
       0,   172,   265,     0,     0,   227,   226,     0,     0,   762,
     510,     0,     0,     0,   466,  1008,   820,   819,     0,   817,
     723,   852,     0,     0,     0,     0,     0,   901,   902,     0,
       0,     0,     0,   712,   914,  1002,    45,     0,     0,     0,
       0,     0,  1116,  1173,  1068,   887,     0,    45,     0,     0,
     251,   231,   495,   764,   753,   740,   733,   738,     0,     0,
     816,   857,   853,     0,     0,     0,     0,     0,     0,     0,
       0,   844,     0,   467,   716,     0,     0,   837,    45,    45,
     880,  1076,  1075,     0,     0,   354,     0,   795,   789,   793,
     167,     0,     0,   465,   818,     0,     0,     0,     0,   850,
     842,     0,   836,     0,   900,   851,     0,   843,     0,   915,
       0,     0,     0,  1115,   888,     0,     0,   496,     0,   743,
       0,   741,   744,   855,   856,     0,   858,   860,     0,     0,
       0,   845,   468,   911,   881,   879,     0,   794,   746,   747,
       0,   739,     0,   854,     0,   849,   835,     0,     0,     0,
       0,   745,   748,   742,   859,     0,     0,   863,   904,   846,
    1013,   749,     0,     0,     0,   861,    45,  1012,   750,   865,
     864,    45,     0,     0,     0,   866,   871,   873,   874,  1014,
    1015,     0,     0,     0,    45,   862,    45,    45,   596,   877,
     876,   875,   867,     0,   869,   870,     0,   872,     0,    45,
     878,   868
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   204,   375,   205,   825,   737,   206,
     892,   605,   789,   675,   555,   890,   891,   432,   893,  1209,
    1482,   207,   208,   606,  1112,  1113,   209,   210,   211,   565,
    1261,  1262,  1116,  1263,   212,   213,   214,   215,  1142,   216,
     217,  1143,   218,   568,   219,   220,   221,   222,  1532,  1533,
     907,  1544,   926,  1801,   223,   224,   225,   226,   227,   228,
     770,  1153,  1154,   229,   230,   231,   732,  1065,  1066,   232,
     233,   696,   443,   919,   920,  1560,   921,   922,  1839,  1570,
    1575,  1576,  1840,  1841,  1571,  1572,  1573,  1562,  1563,  1564,
    1565,  1813,  1567,  1568,  1569,  1815,  2048,  1843,  1844,  1845,
    1155,  1156,  1454,  1455,  1930,  1682,  1134,  1135,   234,   448,
     235,   835,  1947,  1948,  1714,  1715,  1016,   704,   705,  1039,
    1040,  1028,  1029,   236,   742,   743,   744,   745,  1081,  1416,
    1417,  1418,   388,   365,   395,  1306,  1584,  1307,   882,   988,
     608,   627,   609,   610,   611,   612,  1361,  1068,   959,  1853,
     808,   613,   614,   615,   616,   617,  1311,  1586,   618,  1281,
    1850,  1381,  1362,  1382,  1009,  1125,   237,   238,  1893,   239,
     240,   678,  1021,  1022,   695,   414,   241,   242,   243,   244,
    1072,  1073,  1410,  1860,  1861,  1059,   245,   246,   247,   248,
    1191,   249,   962,  1319,   250,   367,   713,  1399,   251,   252,
     253,   254,   255,   638,   630,   968,   969,   970,   256,   257,
     258,   985,   986,   991,   992,   993,  1308,   791,   631,   786,
     550,   259,   260,   261,   699,   262,   715,   716,   263,   753,
     754,   264,   489,   820,   821,   823,   265,   266,   751,   267,
     805,   268,   799,   269,   687,  1056,   270,   271,  2099,  2100,
    2101,  2102,  1669,  1053,   398,   707,   708,  1052,  1634,  1697,
    1884,  1885,  2296,  2297,  2360,  2361,  2379,  2391,  2392,  1702,
    1882,   272,   273,  1684,   659,   794,   795,  1868,  2162,  2163,
    1869,   656,   657,   274,   275,   276,   277,  2012,  2013,  2328,
    2329,   278,   740,   741,   279,   692,   693,   280,   671,   672,
     281,   282,  1131,  1132,  1674,  2089,  2258,  2259,  1913,  1914,
    1915,  1916,  1917,   689,  1918,  1919,  1920,  2312,  1216,  1921,
    1922,  1923,  2261,  2337,  2365,  2366,  2396,  2397,  2414,  2415,
    2416,  2417,  2418,  2429,  1924,  2111,  2278,   801,  1791,  1999,
    2000,  2001,  1925,   813,  1469,  1470,  1942,  1149,  2275,   283,
     284,   285,   286,   287,   288,   289,   290,   782,  1151,  1152,
    1690,  1691,   291,   829,   292,   765,   293,   766,   294,  1128,
     295,   296,   297,   298,   299,  1089,  1090,   300,   748,   301,
     302,   303,   667,   668,   304,   305,  1384,  1624,   701,   306,
     307,   761,   308,   309,   310,   311,   312,   313,   314,  1221,
    1222,   315,  1159,  1698,  1699,  2197,   316,  1662,  2082,  2083,
    1700,   317,  2407,   318,   319,   320,   321,   322,   323,   324,
     325,  1192,  1745,   847,  1723,  1724,  1725,  1749,  1750,  1751,
    2231,  1752,  1753,  1726,  2118,  2322,  2220,   326,  1198,  1773,
     327,   328,   329,   330,  1182,  1727,  1728,  1729,  2226,   331,
    1200,  1777,   332,  1188,  1732,  1733,  1734,   333,   334,   335,
    1194,  1767,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,  1738,  1739,   848,
    1491,   351,   352,   353,   354,   355,   858,   859,   860,  1210,
    1211,  1212,  1217,  1783,  1784,   356,   357,   358,   359,   360,
     361,   362,   363,   865,   866,   867,   868,   870,   871,   872,
     873,   874,   876,   877,   543
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1877
static const yytype_int16 yypact[] =
{
   -1877,   158, -1877, -1877, -1877, -1877,    31,  4391, -1877, -1877,
   -1877,   129, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,   705, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877,    53, -1877, -1877,   268,   160, -1877, -1877, -1877,    53,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877,    92,    92, -1877, -1877, -1877, -1877, -1877,    92,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
     212, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,    92, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877,   234, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
     453,   590, -1877, -1877, -1877, -1877, -1877,    53, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877,    53, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877,   477,   589,   600,    92, -1877, -1877,
   -1877, -1877, -1877, -1877,   366,  1511,   619,   366, -1877, -1877,
   -1877,   633,   660,   667,   675, -1877, -1877, -1877,   493,   697,
      92, -1877, -1877,   761,   780,   845,   894,   601,   148,   918,
     939,   941, -1877,   470, -1877, -1877, -1877,   366, -1877, -1877,
   -1877,   652,   779,  1681,  2278, -1877, -1877,  3042, -1877,   956,
   -1877, -1877,  1418, -1877,   991, -1877,   839,   991,   943, -1877,
   -1877,  1029, -1877, -1877, -1877,  1035,  1038,  1041,  1064,  1092,
   -1877, -1877, -1877, -1877,  1096,   713, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877,  1107, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877,   134,    92,   867,  1006,  1126,   869,
      92,    92,   185,    92, -1877,    92,    92,  1137, -1877,   451,
    1143,    92,    92,    92,    92, -1877, -1877,    92, -1877,  1152,
      92,  1028,    92,  1181, -1877, -1877, -1877,    92, -1877,  1182,
      92, -1877,    92,  1203,   169, -1877,  1028, -1877,    92,    92,
      92,    92, -1877, -1877, -1877, -1877, -1877,    92, -1877,    92,
      92,   619,    92,  1210,   867,    92,  1254, -1877,    92,    92,
   -1877, -1877, -1877,  1201,  1258,    92,    92,  1280,  1283,    92,
     867,  1286,  3042, -1877,  1289,  1305,    92, -1877,  1219,    92,
    1290, -1877,  1347,    92,   867,  1349,  1351, -1877,   869,   867,
      92,    92,  1317,    89,    92,   139, -1877, -1877,   318, -1877,
     484,    92,    92,    92,  1375,    92,    92,  3042,   143, -1877,
   -1877,  1381,    92,    92,    92,    92,    92,  2567,    92, -1877,
     867,    92,   867,    92,    92, -1877, -1877,    92, -1877,   867,
      92,  1385,  1387, -1877,    92, -1877, -1877,  1395, -1877, -1877,
    1397, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877,  1414, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877,    92, -1877, -1877,  1416,  1417,  1424, -1877,
   -1877, -1877, -1877, -1877,  3042,  3042,  3042,  3042,  3042, -1877,
   -1877, -1877, -1877,  1213,   162, -1877, -1877,    92,    92,    92,
      92,  1401, -1877, -1877,  1316,    92,    92, -1877,   763,    92,
      92,    92,    92,    92,   634,    92,  1290,    92,    92,  1210,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,  1204, -1877,
   -1877, -1877, -1877, -1877, -1877,  3042,  3042,  3042, -1877,  3042,
   -1877, -1877, -1877, -1877, -1877, -1877,  3042,  3348, -1877,    63,
    1439, -1877,  1429, -1877,  1202,  1205,  1432, -1877, -1877,  1428,
    3042, -1877, -1877,  2003, -1877, -1877,  1426,  1498,  1439, -1877,
   -1877,   739,   -27, -1877,  2003, -1877, -1877, -1877,  1447,   518,
     125,  3147,  3147,    92,    92,    92,    92,    92,    92,    92,
    1449, -1877,    92, -1877, -1877, -1877,   149, -1877, -1877,  1442,
      92, -1877,  3042, -1877,  1223,   165, -1877,  1443, -1877, -1877,
    1444,  1452, -1877, -1877, -1877, -1877, -1877,  2786,    92,  1450,
   -1877,    92,  1444,    92, -1877,   869, -1877, -1877, -1877, -1877,
   -1877, -1877,  1460, -1877, -1877, -1877, -1877, -1877,  1444, -1877,
   -1877,  1454, -1877, -1877,   665,  1292,    92,   681,   131, -1877,
    1457,  1298,  3042,  1325, -1877,  1467, -1877, -1877,  3042,  3042,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877,    92, -1877,    92,  1461,   308,    92,   619, -1877, -1877,
    1469, -1877,  1470, -1877,  1466,  1167, -1877,  1475, -1877,    92,
   -1877, -1877, -1877,  1476, -1877,  1459,  3385, -1877,    92, -1877,
    5444, -1877,    92,  3042, -1877,  1474, -1877,    92, -1877,    92,
      92,    92,  1439,   532,    92,    92,    92,  1325, -1877,    92,
     617, -1877, -1877, -1877,  1498,   739, -1877, -1877, -1877, -1877,
   -1877, -1877,   134, -1877,  1442,  1484,  1457, -1877, -1877, -1877,
   -1877, -1877, -1877,    92, -1877, -1877, -1877,  5444, -1877,   451,
    1430,    92, -1877,  1481, -1877, -1877, -1877, -1877,  1482,  3419,
     686, -1877, -1877,   234,    92,   619, -1877,    92,  1444, -1877,
    1490,  1487, -1877,    92, -1877,  1503,  3042,  3042, -1877,  1444,
      92,   135,    92,  1229,  1229,   144,  1229, -1877,  1502,   186,
     286,   346,   370,   380,   387, -1877,  1444,   606, -1877,  1512,
   -1877,    99,   150, -1877,   296,   728, -1877, -1877, -1877,   249,
     771, -1877, -1877, -1877, -1877,  1197,   786, -1877,  3460,  5444,
    3491,  3554,  1519,  5444,    92,    92, -1877, -1877, -1877, -1877,
     795, -1877, -1877,  1320,  1444, -1877, -1877, -1877, -1877,  1622,
      92, -1877, -1877, -1877, -1877, -1877, -1877, -1877,  1444, -1877,
   -1877, -1877, -1877,  1521, -1877,  1521, -1877, -1877, -1877, -1877,
     520, -1877,   531, -1877,  1515, -1877, -1877,  3601,  1527,  1528,
    1528,  3171, -1877,  3042,  3042,  3042,  3042,  3042,  3042,  3042,
    3042,  3042,  3042,  3042,  3042,  3042,  3042,  3042,  3042,  3042,
    3042,  3042, -1877,  1472,  1409,  1518,   419,   409,  3042, -1877,
   -1877, -1877,   807,  1358, -1877, -1877, -1877, -1877,   822, -1877,
    1485,   653,  3042,  1531,  1498,  1498,  1498,  1498,  1498, -1877,
     855, -1877,   518,   518,  1439,  1534, -1877,  3147,  5444,    80,
     106, -1877,  1535,  1540, -1877, -1877,  1444, -1877, -1877, -1877,
   -1877,  1444, -1877,   753, -1877,   134, -1877, -1877, -1877,    92,
    3931,    92,  1541,  3042,  1483, -1877, -1877,    92, -1877,  3042,
    3639, -1877,   837, -1877, -1877,  1520, -1877, -1877,   838, -1877,
      92, -1877,    92, -1877, -1877,  1292, -1877, -1877, -1877, -1877,
   -1877,  3965,  1444, -1877, -1877, -1877,  1543,  1545,  1549,  1550,
    1551,  1555, -1877,  1298, -1877,    92, -1877,  3996, -1877, -1877,
      92,  4027,  4058, -1877,  1556,   841,  1547,  1432, -1877, -1877,
      92, -1877,  1565, -1877,  1552, -1877,    92, -1877,  1446,   651,
   -1877, -1877,   241, -1877, -1877,  1569, -1877,  1567,  1582,   842,
   -1877,    92,  1572, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877,  1573, -1877, -1877,   430,  1575,  1579,  4096,  2801,
     -81, -1877,  1561, -1877, -1877,   859, -1877, -1877, -1877, -1877,
   -1877,   875, -1877,  1580,   876, -1877, -1877, -1877,  3042, -1877,
    1194, -1877, -1877, -1877,   877, -1877,  1592, -1877,  1298,  1590,
    1600,   915, -1877, -1877, -1877,  1601, -1877,  1596,  1597,  1587,
      92,  3042,  3042,  2567, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877,  1607,  1608, -1877,   648, -1877, -1877,  4137,  4192, -1877,
    1599, -1877,   436,  1602, -1877, -1877, -1877, -1877,   468, -1877,
   -1877, -1877,   471, -1877,   486,   489,   526, -1877,   534, -1877,
     536, -1877,  1606,  1609,  1611,  1614, -1877,  1615,  1616, -1877,
   -1877, -1877, -1877, -1877, -1877,  1439,  1624,  1612, -1877,  1617,
     -76,   919, -1877,  1621,  1625, -1877, -1877,  1627,  1628,  1629,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,  3042, -1877,
     619,    92,   172, -1877,  1631, -1877,  1632, -1877,  1444, -1877,
   -1877, -1877,  1634, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877,   730, -1877, -1877, -1877,    92,  1444,    84,  1812, -1877,
   -1877,    92,    92, -1877,  1536,   531, -1877,  1637, -1877,  1577,
    3042,  3147, -1877,  3042,  1528,  1528,   446,   446,  3171,  1108,
    2474,  3274,  5444,  3274,  3274,  3274,  3274,  3274,  2474,  2617,
    1528,  2617,  5475,  1518, -1877, -1877,  1633,  1645,  2371, -1877,
   -1877, -1877, -1877, -1877,  1610, -1877, -1877,   869,  5444, -1877,
    3042, -1877, -1877, -1877, -1877,  5444,   517,  5444,  1531,  1531,
    1308,  1531,   616, -1877,  1534,  1648,   518,  4223,  1649,  1650,
    1655,  3147,  3147,  3147, -1877, -1877,    92,  1652, -1877, -1877,
    1653,  1457, -1877,   234, -1877, -1877, -1877, -1877,  1415,   774,
     866, -1877,   921,   869, -1877,   869,   924,  1657,   936, -1877,
    5444,  3042,  2786, -1877,   946, -1877,   869,  1521, -1877,   897,
     967, -1877,   953,  1505,   958, -1877,  2058, -1877,   131, -1877,
    1654,    92,    92,  3042,    92, -1877, -1877,  1444, -1877, -1877,
   -1877,  1433,    92,  3042,    92, -1877,    92, -1877,  1439,  3042,
    1656,  2801, -1877, -1877, -1877, -1877,   964, -1877,  1658, -1877,
    1660,  1661,  1663,  1465,  3042,    92,    92, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877,   867,    92, -1877,  2847,  3228,  1662,
      92,    92, -1877,    92, -1877,   -39,    92, -1877,  3042,    92,
   -1877,  1521,  5444, -1877,  1673,    90,  1673, -1877,    92,  1298,
    1680,  2958,    92,    92, -1877,   451,  3042,   799,  3042,   965,
   -1877,  1677,   984,  5444, -1877,    21, -1877, -1877, -1877, -1877,
   -1877,   867,    52, -1877,    92, -1877,   886, -1877, -1877,   284,
   -1877,   278,   851, -1877,   793, -1877,   382, -1877,   -64, -1877,
      92,    92,    92, -1877,    92,    92,   606, -1877,    92, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877,    92, -1877, -1877,    92,
      92,    92, -1877, -1877,  1354,  1379,  1367,  5444, -1877, -1877,
   -1877,    92,   544, -1877, -1877,  1678, -1877,  1697, -1877, -1877,
    1632, -1877, -1877, -1877, -1877,  5444,  2141, -1877, -1877, -1877,
     569,   462,   462,  1462,  1464, -1877, -1877,  1471,  1473,  1477,
     635,    92, -1877, -1877, -1877, -1877,  1700, -1877, -1877, -1877,
    1637, -1877,  1704, -1877,   107,  1701, -1877,  1703,  4266, -1877,
    1699,  1711,  1432, -1877, -1877,  4338, -1877,  3042,  3042,  1358,
   -1877,  5444,  2003,   518, -1877,   154,  3147,  3147,  3147,   168,
   -1877,   170, -1877,   206, -1877,  1444,    92, -1877,  1518, -1877,
   -1877,  1713,   990, -1877,  1715, -1877,  5444, -1877, -1877, -1877,
    3042, -1877, -1877,  3042, -1877, -1877, -1877, -1877,  5444, -1877,
    1505,  3042,  1712, -1877,  1718,  1719,  4719,  1716, -1877,   152,
      92, -1877,  1009, -1877, -1877,  1710,  5444, -1877, -1877,  4338,
   -1877,  1446, -1877,  1446,    92,    92,    92,  1024,  1043, -1877,
      92,  1728,  1727,  3042,  4753,  2991, -1877, -1877, -1877,  1444,
    1439, -1877, -1877,  1576,  1717,  5444, -1877,    92, -1877,  1737,
    1739, -1877, -1877,  1501,  1749, -1877, -1877,  1752, -1877,  5444,
    1047, -1877,  1049, -1877, -1877,  4784, -1877, -1877,  1065, -1877,
   -1877,  5444,  1740,    92, -1877, -1877, -1877,  1748,  1753,  1562,
    1693,    92,    92,  1751,  1763, -1877,   435, -1877,  1757, -1877,
   -1877, -1877,  1758, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
     886, -1877, -1877, -1877, -1877,   284,    92, -1877, -1877,  1066,
    1759, -1877,  1760, -1877,  1761, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877,   851, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,   793, -1877,
   -1877, -1877, -1877, -1877,   382, -1877, -1877, -1877,   -64,  1756,
    1765,  1767,   802,  1082, -1877,  1770,  1771,  1439, -1877,  1091,
    1104,  1102,  1106,  1113,  1121,  1778, -1877,  1780,  1776,  3042,
    3042, -1877, -1877,  1777, -1877,   966,   544,  2149, -1877,  1122,
   -1877,  5444, -1877, -1877, -1877,  1772, -1877, -1877, -1877, -1877,
     419,   419,   419,   419,   419,  1536, -1877,  1786,  1773,  1787,
    1536,  1701, -1877,   531,   107,   151,   151, -1877, -1877, -1877,
    1127,  1797,  1072,   126, -1877,  1798,   107, -1877,  3042, -1877,
    1791, -1877,  1432, -1877,  2371,  5444,  1785, -1877, -1877,   739,
    1788,  1794,  1130,  1800,  1803,  1810, -1877, -1877, -1877,  1804,
    1518,  1811,   103,   869, -1877,    92,   867,  5444,   103,  5444,
    1505,  3042,  1819,  4818,  1138, -1877, -1877, -1877, -1877, -1877,
    3042, -1877,  1827, -1877, -1877, -1877, -1877, -1877,  1148,  1183,
    1185, -1877, -1877, -1877,   817, -1877,  5444,  3042,  3042,  4852,
   -1877,    92, -1877, -1877,  1717, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877,  1792,    90,  1817,  3385,
   -1877,    92,    92,    92,  2958, -1877, -1877, -1877,   799, -1877,
   -1877, -1877,  2551,    92, -1877, -1877,  1826,  1837, -1877,    92,
      92,  3042, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877,   278, -1877, -1877, -1877,  3042, -1877,  3042,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
    1834,  1835, -1877, -1877, -1877, -1877, -1877,    92,    92, -1877,
    5444,  5444,  1186,  1805, -1877, -1877, -1877,  1838,  4883, -1877,
   -1877, -1877,   569, -1877, -1877, -1877, -1877, -1877, -1877,  1536,
   -1877,    92, -1877, -1877,  1840,  1842, -1877,   959,   126,   126,
     107, -1877,   107,   151,   151,   151,   151,   151,  1157,  4914,
   -1877, -1877, -1877, -1877,  3042, -1877, -1877, -1877, -1877,  1970,
    1843,  1013, -1877,    92,  1853,  1452,    92, -1877,    92, -1877,
    4945, -1877,  3042,  3042, -1877,  4976,  1618,  3042, -1877, -1877,
   -1877, -1877,  1200, -1877, -1877,  5444,  5444,  3042,  1848, -1877,
     872, -1877,  3042, -1877,  1845,  1849, -1877, -1877,  1858,  1866,
   -1877, -1877, -1877, -1877, -1877,  1745,  1859,  1208,  1875,  1876,
    1212,  1003,    92,    92, -1877, -1877,  5444,   801,  1864,     8,
   -1877, -1877,  1850, -1877, -1877,   340,  5007,  5038, -1877, -1877,
   -1877, -1877, -1877,    92,    92,  1104,  1218,  1865,  1882,  1883,
   -1877, -1877, -1877,  1812,  1871, -1877,  1518, -1877,   107, -1877,
    1157,  1872,   126,   126, -1877, -1877, -1877, -1877,  5069, -1877,
    4338, -1877,  1220, -1877,  1020, -1877,   869,  1624, -1877,  1505,
    5444, -1877,  1639, -1877,  1884,  5100,   817, -1877,  5444,  2406,
    1885,  1886,  1887,  1888,  1890,  1892,    92,    92,  1893,  1894,
    5131, -1877, -1877, -1877,  3042,    92,    92, -1877, -1877,  1895,
      92, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
    1904, -1877, -1877, -1877, -1877, -1877,  1226, -1877, -1877, -1877,
   -1877,  1897, -1877, -1877,   611,  1906, -1877,  1908, -1877, -1877,
    1912, -1877, -1877,  1900,  1234,  1157, -1877,  3042,  1970, -1877,
   -1877,  3042,    92,  3042, -1877, -1877, -1877,  5444,  1243, -1877,
   -1877,  1885,    92,    92,    92,    92,    92, -1877, -1877,  3042,
    3042,  3042,  1251, -1877, -1877,  1914, -1877,  1253,  1916,  1295,
      92,  3042, -1877, -1877, -1877, -1877,  3042, -1877,    92,  1903,
   -1877, -1877,  5162, -1877,  5444, -1877, -1877,  1910,  5193,  2406,
   -1877,    67, -1877,  1919,  1302,  1310,  1920,  1322,  1913,  1327,
    5224,  5255,  1911,  5286, -1877,    92,  1857, -1877, -1877, -1877,
   -1877,  1624, -1877,  5317,  5348,   674,  1603, -1877,  1930, -1877,
   -1877,  3042,  1820, -1877, -1877,  1932,  1933,    92,    92, -1877,
   -1877,    92, -1877,  2567, -1877, -1877,  3042, -1877,  3042, -1877,
    1921,  1328,  1338, -1877, -1877,  1928,    92,  5444,    92,  5444,
    1339, -1877, -1877, -1877, -1877,  1350, -1877,  1929,  1357,  1362,
    1368,  5379,  5444, -1877, -1877, -1877,  3042, -1877, -1877,  1931,
    1820, -1877,    92, -1877,  3042, -1877, -1877,  1925,  3042,  1374,
    3042,  1934, -1877, -1877, -1877,  5413,  1378, -1877, -1877,  5444,
    1939, -1877,  3042,  3042,  3042,  1935, -1877, -1877, -1877,  5444,
   -1877, -1877,   -84,   494,  1383, -1877,  1946,  1947, -1877, -1877,
   -1877,  1940,  1940,  1940, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877,   528,  1949, -1877,  1829, -1877,  1393, -1877,
   -1877, -1877
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1877, -1877, -1877, -1877, -1877,     9,  1741,  1073, -1877, -1877,
    -659,   -52, -1877, -1877,  -388, -1877,   718, -1877,   -50,  1070,
   -1877, -1877, -1877,  2029,    35, -1877, -1877, -1877, -1877, -1877,
   -1877,   161,   431,   796, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877,  -171,  -886, -1877, -1877, -1877,   892,   432,  1406,
   -1877,  -167, -1502,   175, -1877, -1877, -1877, -1877, -1877, -1877,
    1407,  -293,  -101, -1877, -1877, -1877,  1403, -1877,  -495, -1877,
   -1877, -1877, -1877,  1293, -1877, -1877,   723, -1249, -1494,  1076,
     429, -1441,  -148,   -41,  1080, -1877,   177,   178, -1747, -1877,
   -1495, -1209, -1493,  -307, -1877,   -11, -1518, -1590,  -629, -1877,
   -1877,   549,   873,   337,   -71,    96, -1877,   568, -1877, -1877,
   -1877, -1877, -1877,   -88, -1877,    76,  -503,  1016, -1877,   993,
     643,   668,  -367, -1877, -1877,   955, -1877, -1877, -1877, -1877,
     384,   383,  1962,   120,  -350, -1264,   184,  -387,  -989,   342,
    -531,  -599,  1278,   609,  1589,  -979,   171, -1877, -1877,  -603,
    -594,  -177, -1877,  -916, -1877,  -583,  -905, -1101, -1877, -1877,
   -1877,   166, -1877, -1877,  1348, -1877, -1877,  1809, -1877,  1813,
   -1877, -1877,   680, -1877,  -373,     0, -1877, -1877,  1814,  1815,
   -1877,   637, -1877,  -722,  -160,  1270, -1877,  1010, -1877, -1877,
    -205, -1877,  1030,   469, -1877,  3696,  -409, -1076, -1877, -1877,
   -1877, -1877, -1877, -1877,  1014, -1877,   472,  -828, -1877, -1877,
   -1877,   397, -1252,  -615,  1078,  -832,  -369,  -423,  -411,   515,
     191, -1877, -1877, -1877,  1423, -1877, -1877,  1011, -1877, -1877,
     978, -1877,  1247, -1876,   913, -1877, -1877, -1877,  1434, -1877,
    1431, -1877,  1435, -1877,  1436,  -984, -1877, -1877, -1877,  -117,
    -198, -1877, -1877, -1877,  -393, -1877,  1171,   692,  -464,   693,
   -1877,    13, -1877, -1877, -1877,  -292, -1877, -1877, -1877, -1511,
   -1877, -1877, -1877, -1877, -1877, -1408,  -541,   159, -1877,  -161,
   -1877,  1299,  1093, -1877, -1877,  1094, -1877, -1877, -1877, -1877,
    -256, -1877, -1877,  1025, -1877, -1877,  1074, -1877,   227,  1086,
   -1877, -1877, -1877,   659, -1877, -1877, -1877,  -193, -1877, -1877,
     193, -1877,  -759,  -375,  -351, -1877, -1877, -1877, -1454, -1877,
   -1877, -1877,  -153, -1877, -1877,  -270, -1877,  -289, -1877,  -308,
   -1877,  -305, -1692, -1017,  -754, -1877,   -80,  -466,  -899, -1847,
   -1877, -1877, -1877,  -480, -1476,   421, -1877,  -734, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877,  -475, -1427,   663,
   -1877,   194, -1877,  1478, -1877,  1635, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1405,   701, -1877,  1384, -1877,
   -1877, -1877, -1877,  1764, -1877, -1877, -1877,   253,  1730, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
     624, -1877, -1877, -1877,   207, -1877, -1877, -1877, -1877,   -32,
   -1850, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877,   573,   392,  -519, -1199,  -947, -1389, -1421, -1413, -1407,
   -1877, -1399, -1397, -1375, -1877, -1877, -1877, -1877, -1877,   374,
   -1877, -1877, -1877, -1877, -1877,   423, -1393, -1382, -1877, -1877,
   -1877,   389, -1877, -1877,   425, -1877,   156, -1877, -1877, -1877,
   -1877,   393, -1877, -1877, -1877, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877, -1877, -1877, -1877,   199, -1877,   208,
     -55, -1877, -1877, -1877, -1877, -1877, -1877, -1877,   960, -1877,
   -1877, -1877,  -801, -1877,   195, -1877, -1877, -1877, -1877, -1877,
   -1877, -1877, -1877, -1877,   949, -1877, -1877, -1877,   950, -1877,
   -1877, -1877, -1877,   948, -1877
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1179
static const yytype_int16 yytable[] =
{
     401,   806,   664,   814,   815,   816,   817,   802,   690,   679,
     413,   413,   855,   960,  1074,  1087,   660,   421,  1439,   702,
    1658,  1269,   574,   576,  1366,  1561,   964,   994,   581,   717,
    1360,   720,   978,   729,   553,  1692,   723,   724,   725,  1581,
    1310,  1310,  1809,  1792,   726,  1794,   447,   728,   777,   730,
    1685,   785,  1313,  1380,  2084,  1812,  1842,  1814,   990,   990,
    1451,  1219,  1789,   415,   928,  1566,  2107,  1828,   466,  1395,
    1063,  1171,   469,  1759,   733,   629,  1172,   797,   952,   629,
     838,  1760,   747,  2032,  1594,   428,   683,  1761,  1341,  -541,
     758,   778,  1707,  1793,  1440,  1762,   393,  1763,  2419,  1541,
    -582,  1765,  2222,  1748,   774,  1758,  1511,  1771,   449,   779,
     989,   989,  1766,   787,  -591,   790,  1876,  1754,  1007,  1764,
    1214,  1772,  1834,  1835,  1836,   464,  -591,  1717,   809,  1832,
    1420,  2045,   366,  -561,  1847,  1320,  1045,  1679,   372,   653,
     824,   654,   827,   580,   364,   542,   393,     8,   379,   833,
     393,   381,   580,   491,   384,  1340,   575,  1005,     2,     3,
    1891,   390,  -592,  2046,  1460,   397,  1834,   887,   567,   400,
    1006,  1218,  1472,   580,  -592,   396,  -585,   887,  -589,  1026,
    -527,   412,  -339,   888,   719,  -527,   978,   419,  -585,  1046,
    -589,   423,   424,   669,   580,  1033,  -582,   429,   430,   710,
    1898,  1899,  1900,   435,   436,  -137,   437,   438,   439,   440,
     979,   441,   971,   981,  -587,  2335,   973,  1047,  1719,   412,
     450,   412,  -591,   980,  1712,   454,  -587,   456,   412,  1708,
    -541,   459,   412,   603,  2420,   463,   412,   465,  2223,  1512,
    1441,  -561,  1513,  1422,   471,  2038,  2039,  2336,   475,   487,
     963, -1103,   478,  1145,   480,  -141,  1837,  1048,  -339,   -61,
   -1128,   488,   490,   412,  2203,   492,   493,  1680,  1049,   967,
    -592,   499,   796,   500,  1088,   393,   431,   504,   684,   412,
     412,   913,  2145,   394,  -585,   629,  -589,  1480,  2236,  -339,
    1227,   412,  2224,  1746,   580,  1756,  1050,  1769,   412,  1775,
    1837,   412, -1050,  2225,   531,  1023,   533,  1018,     4,   953,
    1650,   954,   655,   658,   412,  1736,  2037,  1054,   665,   666,
     670,   666,  -587,   674,   676,  1169,  2084,   682,  1150,   686,
     688,   688,   691,   792,  1070,   694,  1179,  -582,   698,  2035,
     694,  1594,  1816,  1818,  1871,   709,  -137,  1759,   714,  1075,
     694,  1542,   694,  1201,   580,  1760,   413,   694,   694,   694,
    1139,  1761,  1141,  -591,  1314,   694,  1748,   727,   694,  1762,
     694,  1763,   978,  1140,   978,  1765,   738,   739,   580,  1758,
    1754,   978,  -561,   750,   752,  1771,  1766,   757,   580,  1051,
    2033,  1246, -1103,  1764,   764,   580,  -141,   768,   556,  1772,
     -61, -1128, -1139,  1147,   990,  1270,  1892,   412,   722,   781,
    1420,  -592,   788,  1479,  1642,     5,  1412,  1477,   709,   798,
     800,   800,  1127,   804,   781,  -585,  1471,  -589,   582,   810,
     812,   812,   812,   812,   812,  1657,   822,  1167,   954,   826,
    1546,   828,   764, -1050,   580,   831,   629,   412,   834,  1421,
     629,   933,   839,  2152,  2153,   934,  1338,   629,  1228,   897,
    1012,  1951, -1155,  -587,  1407,  1807,  1808,  2370,   497,   909,
     910,   911,   912,  1312,   680,  1686,   580,  1229,   580,   580,
    1587,   856,  2362,   949,   857,  -527, -1158,  1223,   681,   864,
     869,   875,   539,  1344,   580,  1267, -1092,   580,  1345,   396,
     561,   562,   889, -1122,  1224,   894,   895,   896,   682,  1600,
    1602,  1604,   899,   902,   903,   706,  2110,   908,   682,   682,
     682,   682,  2150,  1422,  2097,   916,   917,  1812,  1273,  1814,
    2362,  2228,  -563,   983,   580,  -384,  1268,  2147,   412,  1387,
    1126,   978,   580, -1139,   580,  1747,  1275,  1757,   412,  1770,
    1731,  1776, -1102,  2136,  1557,  1623,  1746,  1274,   603,  1008,
     884,   885,  1799,  1328,  1329,  1330,  1331,  1332,   603,  1756,
    1800,  1184,   900,  1717,  1080,  1769,  1561,  1431,  1432,  1775,
     412,  2031,  1027,  1303, -1127,  1551,  1552, -1049,    50,   607,
    1718,   698,   996,   750,   804,   798,   686,  1001,   498,  -527,
     828,  1003, -1138, -1155,   540, -1154,  2060,   629,   682,   573,
    1433,  1558,  2167,   412,   954,   541,  1566,   563,   832,  1014,
     954,   974,  2421,   549,  -527,   975,   694, -1158,  2229,  1025,
    2245,   682,  2285,  -563,   554,  1138,  1181, -1092,  -527,  2230,
    1187,   557, -1157,  1825, -1122,  1193,  -563,   412,  1197,  1199,
   -1091,  2422, -1121,   977,  1042,   963,  2421,   680,   974,   583,
     412,  1557,   975,  1559,  1719,  1383,  1579,  1720,   558,   624,
     625,   681,  1826,  1035,  1326,   559,   976,   954,  1137,  1064,
    2235,  1069,  -848,   560,  1071,  2422,  1036,  1074,   118,  1043,
     977,  1087,  1087, -1102,  1163,   122,  1082,  1085,   990,  1779,
    1780,  1781,  1044,  1785,  1786,   566,  1114,  1164,  1271,  1115,
    1272,  2423,  -788,  -788,    25,  1121,  1120,  1122,  1558,    29,
     650,   651,  1129,  1166,  1133, -1127,  1168,   682, -1049,   978,
     978,   978,   978,   978,  2435,  2437,  1225,  1537,  1538,  2289,
     655,    47,    48, -1138,   974,  1534, -1154,  2441,   975,  1226,
     989,  1085,  1580,  1202,  1203,   624,   625,   682,   990,   990,
     990,  1320,   976,  1540,  1600,  1602,  1604,   632,   904,   569,
    1559,   640,   682,  2277,  -563,   682,   977,  -382,   905,  1230,
    2031,  1175,  1174, -1157,   760,  1471,  1204,  1471,   570,  1607,
    2309, -1091,  1231, -1121,  1233,    90,  1347,   629,   629,   629,
     629,   629,  1881,  1242,  1696,    95,  2206,  1234,  1747,  2305,
    1599,  1601,  1603,  1220,  1631,  1315,  1243,  2207,  2208,   807,
    1348,  1757,  1696,  2209,  2081,  2210,  2321,  1770,  1316,   819,
    1321,  1776,  1239,   826,  2211,  1349,  2212,  2307,  2213,  1256,
    1350,  1351,  1257,  1322,   637,  1372,  1376,  1352,  1264,  1404,
    1426,   121,  1528,   571,   623,   624,   625,  2304,  1373,  1377,
     974,   628,  1405,  1427,   975,   628,   598,  1443,    46,  -383,
    1276,   624,   625,  1279,   393,   600,  1333,  1740,   976,  2401,
    1444,  1608,  2243,  1446,  1449,  1005,   878,   879,   880,   881,
     883,  2408,   977,  1360,  1638,  1241,  1447,  1450,  1457,  1380,
    -382,    74,   572,   601,  1310,  1310,  1310,  1310,  1310,  1643,
    1265,  1644,   952,  2180,  2369,  2023,  2024,  2025,  2026,  2027,
    1205,  1206,  2019,  1463,  1207,  1208,   577,  1514,  1635,  1609,
    1637,   602,  1238,  2368,    96,  1740,  1464,   927,   929,   930,
    1515,   931,  1610,  1707,  1035,  1613,  1589,   578,   932,   579,
    1590,   642,  1592,   655,  1315,  1926,  1358,  1615,  2161,  1364,
    2214,  1621,   807,  2215,   109,   670,  1625,  1618,   626,  1471,
    -383,   619,  1651,  1703,  1622,  2043,  2044,  1487,   691,  1626,
    2149,  1353,   955,  1490,  1717,  1652,  1704,  1493,   603,  1495,
    1493,  1493,  1238,  1497,  1856,  1499,  1611,   584,  1376,  1185,
    1186,  1718,  1189,  1397,  1010,  1706,   634,  2181,   714,  1619,
    1247,  1874,  1354,   990,   990,   990,  -387,  1238,   663,  1020,
    1630,   661,  1266,  -385,   739,  1988,  1587,  1989,   958,  1641,
    1895,   585,  1238,  1423,   735,   958,  1990,   643,  1991,   752,
     604,  1420,  1717,   644,  2063,  1901,   645,  1041,  2216,   646,
    2068,  1426,  1623,  1248,  1057,  1934,  1355,  1463,  1741,  1718,
    1061,  1062,   772,  2182,  1902,  1862,  1601,  1603,  1935,   780,
    1936,   628,   647,  1938,  1963,  1719,  1445,  1717,  1720,  -230,
    1708,  2183,  1742,  1721,  1660,  1250,  1939,  1964,  2043,  2044,
    1983,  1722,  1743,  2184,  1718,  2185,  2186,  1744,  2187,  1508,
     648,  2188,  1866,  1984,   649,  1118,  2217,  2218,  2219,  1251,
    2002,  1252,  1987,   933,  1703,   652,  1741,   934,  1981,  1982,
    1475,  1463,  1346,  2003,   935,   936,  1988,  2004,  1989,  1703,
    2020,  1711,   412,  1719,  2005,  2040,  1720,  1990,  -585,  1991,
    1742,   662,  2006,  2021,  1253,   949,  2073,  2161,  2041,  1254,
    1743,  1851,   677,  1255,  1422,  1744,  1508,  1256,   685,  2074,
    1257,  1992,  1993,  1506,  1994,  1995,  1910,   697,  1719,  2078,
    1547,  1720,  1620,  2043,  2044,   864,  1721,   700,  1177,  1178,
     869,  1859,  1258,   875,  1722,  1524,  1525,  1526,   703,  1529,
     889,  1508,  2189,  1508,  2138,  1996,  1259,   712,  1952,   974,
    1954,  1955,  1260,   975,  2079,  2272,  2080,  2139,  2176,   746,
     624,   625,  1959,  1539,  1854,  1453,  1163,   976,   718,   682,
    1463,  2177,  1966,  1276,  1968,   731,  1508,   767,  2248,  2199,
      25,   977,   628,  2201,  2281,    29,   628,  1997,  1870,  2237,
    1872,  2249,  2040,   628,  1817,  1819,  1677,  2282,   984,  2051,
    1998,  2299,  1878,   591,   592,  2291,  1880,    47,    48,  1238,
     978,  1463,  1992,  1993,  2300,  1994,  1995,  1894,   635,   736,
     639,   641,  2314,   749,  2317,  1284,  1285,  1286,  1287,  1288,
    1289,  1290,  1291,  1292,  1293,  1294,  1295,  1296,  1297,  1298,
    1299,  1300,  1301,  1302,  1605,   755,  1996,  1037,   756,  1038,
     807,   759,   593,  2319,   762,  1318,   594,   595,   596,   597,
    1426,    90,  1325,   974,  1327,  1546,  2320,   975,  1508,   598,
     763,    95,   783,  2339,   624,   625,   599,   769,   600,  1337,
    1463,  2340,   784,   624,   625,  1703,  2002,   886,  1997,  1633,
    1633,  2251,  1633,  2342,   598,   977,  2002,  2380,  2344,  2374,
     694,  1998,  1064,   600,  1064,   883,   601,  1645,  2382,  2375,
    2381,  1370,   771,  1317,   775,  1426,   776,   121,   593,  1535,
    1463,  2383,   594,   595,   596,   597,  1163,  1041,  2385,  1334,
    1335,   601,  1238,  2386,   602,   598,  2404,  2389,  1668,  2387,
     803,  2424,   599,   628,   600,  2400,   811,  1133,  1079,  2405,
     836,  1583,   837,  1681,  2425,  2430,  2431,  1683,   898,   602,
     840,   150,   842,   682,  2440,   629,  2154,  2155,  2156,  2351,
    2352,   412,   601,   621,  1195,  1196,  1709,   622,  1710, -1178,
    1713,   861,   862,   623,   624,   625,  1863,  1864,  1865,   863,
     901,   603,   954,   925,   955,   598,   626,   958,   956,   961,
     602,   957,   972,  1782,   600,   982,  1002,   792,  1013,  1015,
    1017,  1438,  2274,  1011,  1220,  1024,   603,  1790,  1030,  1034,
    1215,  1215,   396,  1055,  1058,  1060,   952,  1076,  1077,  1798,
    1452,  1078,   601,  1083,  1091,  1092,  1115,   412,  1805,  1119,
    1323,  1146,  1157,   604,  1324,   593,  1160,  1161,  1170,   594,
     595,   596,   597,   883,  1473,   819,  2064,   603,  1173,  1827,
     602,  1176,   598,   784,   624,   625,  1184,  1190,   604,   599,
    1213,   600,  1838,  1232,   967,   598,  2066,  1238,  1087,   580,
    1280,  2308,  1471,  1244,   600,  1283,  1304,   934,  1305,  -342,
     975,  1645,  1336,  1342,  1645,  1645,  1645,   626,  1343,   601,
    1367,  1550,  1551,  1552,  1867,  1406,  1365,  1375,  1389,   604,
    1390,  2051,   601,  1553,  1391,  1392,  1393,   603,  2109,   711,
    1394,  1403,  1554,  1409,    25,  1415,  -927,   602,  1411,    29,
    1527,  2349,  1424,   628,   628,   628,   628,   628,   694,  1425,
     602,   984,   984,  1429,  1430,  1555,  1434,  1435,  1442,  1458,
    1556,    47,    48,  2367,  1087,  1461,  1448,  1462,  1903,  1465,
    1545,  1466,  1467,  1468,   412,  1476,  1478,  1588,   772,   604,
    1485,  1500,  1578,  1488,  1501,  1071,  1502,   626,  1557,  1503,
    1504,  1505,  1508,  1509,   603,   551,  1516,   904,  1510,  1577,
    1517,   772,  1519,  1520,  1521,  2202,  1531,   603,  2367,  1536,
    1585,  2143,  1574,  1583,  1582,    90,  1593,  1596,  1597,  1945,
    1946,  2146,  1591,  1598,  1614,    95,  1247,   364,   394,  1631,
    1606,   967,  1640,  1421,  1653,  1654,  1655,  1648,  1656,  1408,
     841,  1678,   843,  1667,  1962,  1558,   604,  1687,  1795,   844,
     845,   846,  1705,  1802,  1796,   849,   850,   851,   852,   604,
     853,   854,  1797,   734,  1804,  1830,  2267,  2268,  1820,  1248,
    1821,   121,  1833,  1616,  1020,  1249,  1846,  1822,  1848,  1823,
    1851,  1873,  1875,  1824,  1890,  1912,    13,    14,  1628,    15,
      16,   734,  1852,  1886,    20,  1636,  -494,  1559,   734,  1887,
    1888,  1250,    23,  1904,   552,   883,   793,    27,  1905,  1911,
      30,  1646,  1928,  1649,  1929,   150,  1931,  1932,    37,  1933,
      38,  1940,    40,  1943,  1707,  1251,   883,  1252,  1944,  1949,
    1708,  1950,  1953,  1956,  1965,  1967,  1969,  1978,  2029,  1664,
    2022,  2034,  1838,  1838,  1838,    59,  1979,  2303,  1980,  2306,
    1675,  1985,  1986,  2007,  1838,  2008,    70,  2009,  2014,  2250,
    1253,  -381,  2030,  1689,  2042,  1254,  2053,  2047,  1695,  1255,
    1701,  2050,  2140,  1256,  2054,  2055,  1257,  1543,  2092,  2059,
      85,  2056,   593,   670,  2057,  1696,   594,   595,   596,   597,
     593,  2058,  2061,    93,   594,   595,   596,   597,  1258,   598,
    2071,  2076,  2077,  2094,  2112,  2113,   599,   598,   600,  2133,
    2134,   102,  1259,   914,   599,  -224,   600,   104,  1260,  2141,
    2358,  2166,  2090,  2179,  2164,   108,  2192,   110,  2148,   112,
    2193,   114,  2174,  2194,  2195,  1681,   601,  2196,   119,  1867,
    2198,  2098,  -839,  2200,   601,  2221,  2238,  2227,  1811,  2239,
    2240,  2108,  2242,  2246,  2252,   130,   131,  2114,  1713,  2253,
    2260,  2262,  2263,  2264,   602,  2265,  2119,  2266,  2269,  2270,
    2276,  2280,   602,   143,  2286,  2125,  2287,   734,  2284,  2288,
     590,  2290,  2315,  2318,  2330,  2332,  2338,  2341,  2343,  1855,
     807,  1318,  2347,  1782,   155,  2350,  2355,   156,  2356,  2363,
    2364,   412,  2373,  2376,  2384,   984,  2398,  2406,  2390,   412,
    2411,  2402,  2135,  2426,  2427,  2428,  2439,  2421,  1240,   564,
    1530,   603,  1877,  1245,  2095,  1879,  2015,  1803,  1148,   603,
    1481,  1419,  1806,  1883,   906,  2159,  2241,  1437,   967,  1827,
     593,  2016,   918,   915,   594,   595,   596,   597,  1838,  1031,
    1838,  1838,  1838,  1838,  1838,  1838,  1549,   598,  1277,  1831,
    2244,  2151,  1278,  2028,   599,  1906,   600,  1909,   965,  1067,
    2036,  2144,   966,   604,  1694,  1927,  1456,  1676,   784,   624,
     625,   604,  2191,  2093,  2172,  2205,  2115,  1086,  1385,  1627,
     598,  1368,  1414,  1612,   601,  1896,  1897,   427,  2052,   600,
    1117,  2438,   773,  2062,  2067,  1032,  1647,  1136,  1123,  1124,
    1670,   586,  1617,  1130,  1374,   587,   588,   589,  1857,   800,
    2204,  1946,   602,  1037,  1858,  1339,   995,   601,   593,  1428,
    1165,  1400,   594,   595,   596,   597,  1474,   998,  2273,   997,
    1629,  1086,   999,  1632,  1000,   598,  2171,  2293,  2393,  1158,
    2096,  1144,   599,  1716,   600,   602,  1838,  1356,  1357,   412,
    2377,  1413,  2065,  1369,  1378,  1672,  2334,  2091,  2302,  1215,
    1215,  1215,  2394,  1215,  1215,  2410,  2432,  1787,  1180,   603,
    1183,  2434,   601,  2279,  1941,  1215,  1693,  1659,  2103,   830,
    1004,  1084,   626,  2069,   812,   812,   721,   673,  1788,   734,
     734,  2010,  2011,  2098,  2255,  2104,  1810,  1971,  1975,  2018,
     602,   593,   603,  1958,  2017,   594,   595,   596,   597,   593,
    1961,  1973,  2124,   594,   595,   596,   597,  1977,   598,   967,
    2122,   604,  2283,  1507,  1518,   599,   598,   600,  2132,     0,
    1522,  1523,     0,   599,     0,   600,     0,   412,     0,     0,
    2049,     0,     0,     0,     0,     0,  1585,     0,     0,     0,
    2295,   628,   984,     0,   604,   601,     0,   603,     0,     0,
    1085,     0,  1085,   601,  1388,     0,     0,     0,     0,     0,
       0,     0,     0,  2070,     0,  1396,  2316,     0,     0,     0,
       0,     0,  2075,   602,  1309,  1309,  2327,  2326,     0,     0,
       0,   602,     0,     0,     0,     0,     0,     0,     0,  2085,
    2086,     0,     0,     0,     0,     0,     0,     0,     0,   604,
     734,   734,     0,  1215,  1215,  1215,     0,     0,  1790,  1790,
     412,     0,     0,     0,     0,     0,  1689,     0,   412,     0,
       0,     0,     0,     0,   819,     0,     0,  1359,     0,     0,
     603,     0,     0,  2116,     0,     0,     0,     0,   603,     0,
       0,     0,     0,     0,  2327,     0,  2378,     0,     0,  2126,
    1379,  2127,     0,     0,     0,     0,     0,     0,  1459,     0,
       0,     0,     0,    13,    14,     0,    15,    16,     0,     0,
       0,    20,     0,     0,     0,     0,     0,     0,     0,    23,
       0,     0,   604,     0,    27,     0,     0,    30,   734,     0,
     604,     0,  1486,     0,     0,    37,  2412,    38,  1489,    40,
       0,  2413,  1492,     0,  1494,     0,     0,     0,  1496,     0,
    1498,     0,     0,     0,  2413,     0,  2433,  2436,  1437,     0,
       0,   593,    59,     0,     0,   594,   595,   596,   597,  2436,
       0,     0,     0,    70,     0,     0,  2158,     0,   598,     0,
       0,  2160,     0,     0,     0,   599,     0,   600,     0,     0,
       0,  2256,     0,     0,  2170,  1883,   593,    85,     0,  2175,
     594,   595,   596,   597,     0,     0,     0,     0,     0,  2178,
      93,     0,     0,   598,  2190,   601,     0,     0,  1086,     0,
     599,     0,   600,     0,     0,     0,     0,     0,   102,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,   108,   602,   110,     0,   112,     0,   114,     0,
     601,     0,     0,     0,     0,   119,     0,     0,     0,   933,
       0,   772,     0,   934,     0,  1545,     0,   772,     0,     0,
     935,   936,   130,   131,     0,     0,   937,   938,   602,   940,
     412,     0,   942,   943,   944,   945,   946,     0,     0,   948,
     143,   949,   950,     0,     0,     0,     0,     0,     0,     0,
     603,  2257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155,     0,     0,   156,   412,   883,   967,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1548,     0,     0,     0,     0,   603,     0,     0,   818,     0,
       0,   593,     0,     0,     0,   594,   595,   596,   597,     0,
    1639,     0,   604,     0,   818,     0,     0,   593,   598,     0,
       0,   594,   595,   596,   597,   599,     0,   600,     0,  2292,
    2160,     0,     0,  2294,   598,  2298,     0,     0,     0,     0,
       0,   599,     0,   600,     0,     0,     0,   604,     0,     0,
       0,  2310,  2311,  2313,   734,   601,  1215,     0,  1673,     0,
       0,     0,   933,  2323,     0,     0,   934,     0,  2324,  2106,
       0,   601,     0,   935,   936,     0,   951,     0,     0,   937,
     938,  2257,   940,   602,     0,   942,   943,   944,   945,   946,
       0,     0,     0,     0,   949,     0,     0,     0,  1730,   602,
       0,  1735,     0,     0,  1755,     0,  1768,     0,  1774,     0,
    1778,     0,     0,  2357,  2359,  1215,     0,     0,     0,     0,
     412,     0,  1067,     0,  1067,   819,     0,     0,  2371,     0,
    2372,     0,     0,     0,     0,     0,   412,     0,     0,     0,
     603,     0,     0,  1086,  1086,     0,     0,     0,     0,     0,
       0,     0,     0,  1661,     0,     0,   603,     0,   883,   734,
       0,  1671,  2359,     0,  1130,     0,  2395,     0,     0,     0,
    2399,     0,  1701,     0,     0,     0,   793,     0,     0,     0,
    1086,  1086,  2234,  1215,  1701,  2409,  2395,     0,     0,     0,
       0,     0,   604,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   734,     0,     0,     0,     0,     0,   604,  1737,
       0,     0,     0,     0,     0,     0,     0,     0,   734,   734,
     734,     0,   734,   734,     0,  1111,   734,     0,     0,   951,
       0,     0,     0,  1019,   734,     0,   593,  1086,  1086,  1086,
     594,   595,   596,   597,     0,     0,     0,     0,  1437,     0,
       0,   593,     0,   598,     0,   594,   595,   596,   597,     0,
     599,     0,   600,     0,     0,     0,     0,     0,   598,     0,
       0,     0,     0,     0,     0,   599,   951,   600,     0,  1829,
       0,     0,     0,     0,     0,     0,     0,     0,   951,     0,
     601,     0,     0,     0,  1663,     0,     0,   593,     0,     0,
       0,   594,   595,   596,   597,   601,     0,     0,     0,     0,
       0,   734,  1215,     0,   598,     0,     0,     0,   602,     0,
       0,   599,     0,   600,     0,     0,     0,     0,     0,  1215,
       0,     0,     0,   602,     0,  2325,     0,     0,  1957,     0,
       0,     0,     0,  1960,     0,     0,     0,   951,   951,   951,
     951,   601,   951,     0,     0,   412,  1970,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     412,     0,   734,   734,   734,   603,     0,     0,  1972,   602,
       0,     0,     0,     0,  1974,     0,     0,     0,  1976,     0,
     603,     0,     0,     0,     0,     0,   951,     0,   951,   951,
     951,   951,     0,     0,     0,  1688,     0,     0,   593,     0,
       0,     0,   594,   595,   596,   597,   412,     0,     0,     0,
       0,  1086,     0,     0,     0,   598,     0,   604,     0,     0,
       0,     0,   599,     0,   600,     0,   603,     0,  1908,     0,
       0,   593,   604,     0,     0,   594,   595,   596,   597,     0,
       0,     0,     0,     0,     0,     0,     0,   951,   598,     0,
       0,     0,   601,     0,     0,   599,     0,   600,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   951,
       0,     0,     0,     0,     0,     0,     0,     0,   604,   951,
     602,     0,   593,     0,     0,   601,   594,   595,   596,   597,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   598,
     951,     0,     0,     0,     0,     0,   599,     0,   600,     0,
       0,     0,     0,   602,     0,     0,   951,   412,     0,     0,
     951,   951,     0,     0,     0,     0,     0,     0,  1309,  1309,
    1309,  1309,  1309,     0,     0,     0,   601,   603,     0,     0,
       0,  2105,     0,     0,     0,     0,     0,     0,     0,     0,
     412,     0,     0,     0,  2117,     0,     0,     0,     0,  2120,
       0,     0,  2121,     0,   602,     0,     0,     0,     0,     0,
     603,     0,  2128,     0,  2129,     0,  2130,   951,  2131,     0,
    1359,     0,     0,     0,     0,     0,  1379,   593,     0,   604,
       0,   594,   987,   596,   597,     0,     0,     0,     0,     0,
       0,   412,     0,     0,   598,     0,   933,     0,     0,     0,
     934,   599,     0,   600,     0,     0,     0,   935,   936,  2088,
       0,   603,   604,     0,   938,     0,   940,     0,     0,   942,
     943,   944,   945,   946,     0,     0,   951,   951,   949,     0,
     793,   601,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1086,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   933,     0,  1665,     0,   934,   593,   602,
       0,  2123,     0,   604,   935,   936,     0,     0,     0,  1666,
     937,   938,   939,   940,     0,     0,   942,   943,   944,   945,
     946,   947,     0,   948,     0,   949,   950,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   412,     0,     0,   933,
       0,     0,     0,   934,     0,   734,  2137,     0,     0,     0,
     935,   936,     0,     0,     0,     0,   603,   938,     0, -1179,
       0,     0, -1179, -1179, -1179, -1179, -1179,     0,     0,  1829,
       0,   949,     0,   951,   951,   951,   951,   951,   951,   951,
     951,   951,   951,   951,   951,   951,   951,   951,   951,   951,
     951,   951,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2165,     0,     0,   734,     0,  2168,   951,   604,     0,
       0,     0,     0,   933,   951,     0,   951,   934,   593,     0,
       0,     0,     0,     0,   935,   936,   951,     0,     0,     0,
     937,   938,   939,   940,   941,     0,   942,   943,   944,   945,
     946,   947,     0,   948,     0,   949,   950,     0,     0,     0,
    1093,     0,     0,     0,  1094,   593,     0,     0,     0,   951,
       0,  1095,  1096,     0,     0,     0,     0,  1097,  1098,  1099,
    1100,   734,   734,  1101,  1102,  1103,  1104,  1105,  1106,  1107,
    1108,     0,  1109,  1110,   933,     0,  1162,     0,   934,   593,
       0,  2301,     0,     0,     0,   935,   936,     0,     0,     0,
       0,   937,   938,   939,   940,     0,     0,   942,   943,   944,
     945,   946,   947,     0,   948,     0,   949,   950,     0,     0,
       0,     0,     0,     0,     0,   933,     0,   951,  1235,   934,
     593,     0,     0,     0,  1086,     0,   935,   936,  1086,     0,
       0,   951,   937,   938,   939,   940,     0,     0,   942,   943,
     944,   945,   946,   947,     0,   948,   933,   949,   950,  1236,
     934,   593,   951,     0,     0,     0,     0,   935,   936,     0,
       0,     0,     0,   937,   938,   939,   940,     0,     0,   942,
     943,   944,   945,   946,   947,     0,   948,     0,   949,   950,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1086,   734,  1086,  1086,  1086,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   951,     0,   734,   933,
       0,     0,  1237,   934,   593,     0,     0,     0,     0,     0,
     935,   936,     0,     0,   951,     0,   937,   938,   939,   940,
       0,     0,   942,   943,   944,   945,   946,   947,     0,   948,
       0,   949,   950,  1086,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   933,   951,     0,     0,
     934,   593,     0,     0,   951,  1086,  1086,   935,   936,  1086,
     951,     0,  1282,   937,   938,   939,   940,     0,     0,   942,
     943,   944,   945,   946,   947,     0,   948,     0,   949,   950,
       0,     0,     0,     0,   933,   951,  1371,     0,   934,   593,
       0,     0,     0,     0,     0,   935,   936,   951,     0,     0,
    1086,   937,   938,   939,   940,   951,     0,   942,   943,   944,
     945,   946,   947,     0,   948,   951,   949,   950,   951,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   951,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   951,     0,     0,     0,     0,     0,
     368,   369,   370,   371,     0,   373,     0,   374,   951,   376,
     377,     0,   378,     0,   951,     0,   380,     0,   382,   383,
     951,     0,   385,   386,   387,     0,   389,     0,   391,   392,
       0,     0,   399,     0,     0,     0,     0,   402,   403,   404,
     405,   406,   407,   408,   409,     0,   410,   411,     0,     0,
     416,   417,   418,     0,   420,     0,   422,     0,     0,   425,
     426,     0,     0,     0,     0,     0,     0,   433,   434,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   442,     0,
     444,     0,   445,   446,     0,     0,     0,   451,   452,   453,
       0,     0,   455,     0,     0,   457,   458,     0,   460,   461,
     462,     0,     0,     0,     0,   467,   468,     0,     0,   470,
       0,   472,   473,   474,     0,   476,   477,     0,     0,   479,
       0,   481,   482,   483,   484,   485,   486,     0,     0,     0,
     951,     0,     0,   494,   495,   496,     0,     0,     0,     0,
     501,   502,   503,     0,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
       0,   532,     0,   534,   951,   535,     0,   536,   537,   538,
       0,     0,     0,     0,     0,   544,   545,   546,   547,   548,
       0,     0,     0,     0,     0,     0,   951,     0,   951,     0,
       0,     0,   951,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   951,   933,     0,   951,     0,
     934,   593,     0,     0,     0,     0,   620,   935,   936,   633,
       0,   636,  1363,   937,   938,   939,   940,     0,  1111,   942,
     943,   944,   945,   946,   947,     0,   948,     0,   949,   950,
     933,     0,  1386,     0,   934,   593,     0,     0,     0,     0,
       0,   935,   936,     0,     0,     0,     0,   937,   938,   939,
     940,     0,     0,   942,   943,   944,   945,   946,   947,     0,
     948,   933,   949,   950,     0,   934,   593,     0,     0,     0,
       0,     0,   935,   936,     0,     0,     0,  1398,   937,   938,
     939,   940,     0,     0,   942,   943,   944,   945,   946,   947,
       0,   948,   933,   949,   950,     0,   934,   593,     0,   951,
     951,     0,     0,   935,   936,     0,     0,   951,  1401,   937,
     938,   939,   940,     0,     0,   942,   943,   944,   945,   946,
     947,     0,   948,   933,   949,   950,     0,   934,   593,     0,
       0,     0,     0,     0,   935,   936,     0,     0,   951,  1402,
     937,   938,   939,   940,     0,     0,   942,   943,   944,   945,
     946,   947,     0,   948,     0,   949,   950,     0,     0,   951,
       0,   933,     0,     0,   951,   934,   593,     0,     0,     0,
       0,     0,   935,   936,   951,   951,     0,  1436,   937,   938,
     939,   940,     0,     0,   942,   943,   944,   945,   946,   947,
       0,   948,     0,   949,   950,     0,     0,     0,     0,     0,
       0,     0,   933,     0,     0,   951,   934,   593,     0,     0,
       0,     0,     0,   935,   936,   951,   951,     0,  1483,   937,
     938,   939,   940,     0,     0,   942,   943,   944,   945,   946,
     947,     0,   948,     0,   949,   950,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   951,     0,   951,
       0,     0,     0,     0,     0,     0,     0,   933,     0,   951,
       0,   934,   593,     0,   951,     0,     0,   951,   935,   936,
       0,     0,     0,  1484,   937,   938,   939,   940,     0,   951,
     942,   943,   944,   945,   946,   947,     0,   948,   933,   949,
     950,     0,   934,   593,     0,     0,     0,     0,     0,   935,
     936,     0,     0,     0,  1595,   937,   938,   939,   940,     0,
       0,   942,   943,   944,   945,   946,   947,     0,   948,     0,
     949,   950,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   933,     0,     0,     0,   934,   593,     0,     0,     0,
     923,   924,   935,   936,     0,     0,   951,  1849,   937,   938,
     939,   940,     0,     0,   942,   943,   944,   945,   946,   947,
       0,   948,     0,   949,   950,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   951,     0,   951,     0,     0,     0,   951,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   951,
     951,     0,   951,   933,     0,  1665,     0,   934,   593,     0,
       0,     0,   951,   951,   935,   936,     0,     0,     0,     0,
     937,   938,   939,   940,     0,     0,   942,   943,   944,   945,
     946,   947,     0,   948,     0,   949,   950,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   951,     0,   951,     0,
       0,     0,     0,     0,     0,     0,     0,     9,     0,     0,
     951,   951,     0,     0,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   951,     0,     0,     0,   951,     0,
       0,     0,     0,     0,    11,    12,    13,    14,   951,    15,
      16,    17,    18,    19,    20,     0,     0,    21,    22,     0,
       0,     0,    23,    24,    25,     0,    26,    27,    28,    29,
      30,    31,     0,    32,    33,    34,    35,    36,    37,     0,
      38,    39,    40,    41,    42,    43,     0,     0,    44,    45,
      46,    47,    48,     0,     0,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,     0,    71,     0,
      72,    73,     0,    74,    75,    76,     0,     0,    77,     0,
       0,    78,    79,     0,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,    91,    92,     0,     0,
       0,     0,     0,    93,    94,    95,    96,     0,     0,     0,
       0,    97,     0,     0,    98,    99,     0,     0,   100,   101,
       0,   102,     0,     0,     0,   103,     0,   104,     0,   105,
       0,     0,     0,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     0,   116,   117,   118,     0,   119,     0,
     120,   121,     0,   122,     0,   123,   124,   125,   126,     0,
       0,   127,   128,   129,     0,   130,   131,   132,     0,   133,
     134,   135,     0,   136,     0,   137,   138,   139,   140,   141,
       0,   142,     0,   143,   144,     0,     0,   145,   146,   147,
       0,     0,   148,   149,     0,   150,   151,     0,   152,   153,
       0,     0,     0,   154,   155,     0,     0,   156,     0,     0,
     157,     0,     0,     0,   158,   159,     0,     0,   160,   161,
     162,     0,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,   174,     0,     0,   175,     0,     0,
       0,   176,   177,   178,   179,   180,     0,   181,   182,     0,
       0,   183,   184,   185,   186,     0,     0,     0,     0,   187,
     188,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,   196,     0,   197,   198,
     199,   200,   201,   202,   933,     0,     0,   203,   934,   593,
       0,     0,     0,     0,     0,   935,   936,     0,     0,     0,
    1889,   937,   938,   939,   940,     0,     0,   942,   943,   944,
     945,   946,   947,     0,   948,     0,   949,   950,   933,     0,
    1907,     0,   934,   593,     0,     0,     0,     0,     0,   935,
     936,     0,     0,     0,     0,   937,   938,   939,   940,     0,
       0,   942,   943,   944,   945,   946,   947,     0,   948,   933,
     949,   950,     0,   934,   593,     0,     0,     0,     0,     0,
     935,   936,     0,     0,     0,  1937,   937,   938,   939,   940,
       0,     0,   942,   943,   944,   945,   946,   947,     0,   948,
       0,   949,   950,   933,     0,  2072,     0,   934,   593,     0,
       0,     0,     0,     0,   935,   936,     0,     0,     0,     0,
     937,   938,   939,   940,     0,     0,   942,   943,   944,   945,
     946,   947,     0,   948,     0,   949,   950,   933,     0,  2087,
       0,   934,   593,     0,     0,     0,     0,     0,   935,   936,
       0,     0,     0,     0,   937,   938,   939,   940,     0,     0,
     942,   943,   944,   945,   946,   947,     0,   948,   933,   949,
     950,     0,   934,   593,     0,     0,     0,     0,     0,   935,
     936,     0,     0,     0,  2142,   937,   938,   939,   940,     0,
       0,   942,   943,   944,   945,   946,   947,     0,   948,   933,
     949,   950,     0,   934,   593,     0,     0,     0,     0,     0,
     935,   936,     0,     0,     0,  2157,   937,   938,   939,   940,
       0,     0,   942,   943,   944,   945,   946,   947,     0,   948,
     933,   949,   950,  2169,   934,   593,     0,     0,     0,     0,
       0,   935,   936,     0,     0,     0,     0,   937,   938,   939,
     940,     0,     0,   942,   943,   944,   945,   946,   947,     0,
     948,   933,   949,   950,     0,   934,   593,     0,     0,     0,
       0,     0,   935,   936,     0,     0,     0,  2173,   937,   938,
     939,   940,     0,     0,   942,   943,   944,   945,   946,   947,
       0,   948,   933,   949,   950,     0,   934,   593,     0,     0,
       0,     0,     0,   935,   936,     0,     0,     0,  2232,   937,
     938,   939,   940,     0,     0,   942,   943,   944,   945,   946,
     947,     0,   948,   933,   949,   950,     0,   934,   593,     0,
       0,     0,     0,     0,   935,   936,     0,     0,     0,  2233,
     937,   938,   939,   940,     0,     0,   942,   943,   944,   945,
     946,   947,     0,   948,   933,   949,   950,  2247,   934,   593,
       0,     0,     0,     0,     0,   935,   936,     0,     0,     0,
       0,   937,   938,   939,   940,     0,     0,   942,   943,   944,
     945,   946,   947,     0,   948,   933,   949,   950,     0,   934,
     593,     0,     0,     0,     0,     0,   935,   936,     0,     0,
       0,  2254,   937,   938,   939,   940,     0,     0,   942,   943,
     944,   945,   946,   947,     0,   948,   933,   949,   950,  2271,
     934,   593,     0,     0,     0,     0,     0,   935,   936,     0,
       0,     0,     0,   937,   938,   939,   940,     0,     0,   942,
     943,   944,   945,   946,   947,     0,   948,   933,   949,   950,
    2331,   934,   593,     0,     0,     0,     0,     0,   935,   936,
       0,     0,     0,     0,   937,   938,   939,   940,     0,     0,
     942,   943,   944,   945,   946,   947,     0,   948,   933,   949,
     950,     0,   934,   593,     0,     0,     0,     0,     0,   935,
     936,     0,     0,     0,  2333,   937,   938,   939,   940,     0,
       0,   942,   943,   944,   945,   946,   947,     0,   948,   933,
     949,   950,     0,   934,   593,     0,     0,     0,     0,     0,
     935,   936,     0,     0,     0,  2345,   937,   938,   939,   940,
       0,     0,   942,   943,   944,   945,   946,   947,     0,   948,
     933,   949,   950,  2346,   934,   593,     0,     0,     0,     0,
       0,   935,   936,     0,     0,     0,     0,   937,   938,   939,
     940,     0,     0,   942,   943,   944,   945,   946,   947,     0,
     948,   933,   949,   950,  2348,   934,   593,     0,     0,     0,
       0,     0,   935,   936,     0,     0,     0,     0,   937,   938,
     939,   940,     0,     0,   942,   943,   944,   945,   946,   947,
       0,   948,   933,   949,   950,     0,   934,   593,     0,     0,
       0,     0,     0,   935,   936,     0,     0,     0,  2353,   937,
     938,   939,   940,     0,     0,   942,   943,   944,   945,   946,
     947,     0,   948,   933,   949,   950,     0,   934,   593,     0,
       0,     0,     0,     0,   935,   936,     0,     0,     0,  2354,
     937,   938,   939,   940,     0,     0,   942,   943,   944,   945,
     946,   947,     0,   948,   933,   949,   950,  2388,   934,   593,
       0,     0,     0,     0,     0,   935,   936,     0,     0,     0,
       0,   937,   938,   939,   940,     0,     0,   942,   943,   944,
     945,   946,   947,     0,   948,     0,   949,   950,   933,     0,
    2403,     0,   934,   593,     0,     0,     0,     0,     0,   935,
     936,     0,     0,     0,     0,   937,   938,   939,   940,     0,
       0,   942,   943,   944,   945,   946,   947,     0,   948,   933,
     949,   950,     0,   934,   593,     0,     0,     0,     0,     0,
     935,   936,     0,     0,     0,     0,   937,   938,   939,   940,
       0,     0,   942,   943,   944,   945,   946,   947,     0,   948,
     933,   949,   950,     0,   934,     0,     0,     0,     0,     0,
       0,   935,   936,     0,     0,     0,     0,   937,   938,   939,
     940,     0,     0,   942,   943,   944,   945,   946,   947,     0,
     948,     0,   949,   950
};

static const yytype_int16 yycheck[] =
{
      50,   476,   369,   483,   484,   485,   486,   473,   383,   378,
      62,    63,   531,   616,   736,   749,   366,    69,  1119,   392,
    1425,   907,   227,   228,  1013,  1274,   620,   642,   233,   402,
    1009,   404,   631,   421,   205,  1462,   409,   410,   411,  1303,
     956,   957,  1544,  1519,   417,  1521,    98,   420,   457,   422,
    1458,   462,   957,  1032,  1904,  1550,  1574,  1550,   641,   642,
    1136,   862,  1516,    63,   595,  1274,  1942,  1561,   118,  1053,
     729,   830,   122,  1494,   424,   252,   830,   470,    15,   256,
     503,  1494,   433,  1830,  1336,    76,   379,  1494,     8,   116,
     440,   458,    71,  1520,   175,  1494,     7,  1494,   182,    15,
      20,  1494,    94,  1492,   454,  1494,   182,  1496,    99,   459,
     641,   642,  1494,   463,     8,   465,  1618,  1492,   659,  1494,
      21,  1496,    15,    16,    17,   116,    20,   191,   478,  1570,
     169,     5,    12,     8,  1575,   963,     5,    47,    18,     5,
     490,     7,   492,     8,    15,   197,     7,   116,    28,   499,
       7,    31,     8,   144,    34,   987,     8,     8,     0,     1,
       8,    41,     8,    37,  1148,    45,    15,     5,   220,    49,
      21,    21,  1161,     8,    20,    15,     8,     5,     8,   682,
      15,   129,   129,    21,    15,    37,   785,    67,    20,    58,
      20,    71,    72,     8,     8,   698,   116,    77,    78,   397,
    1654,  1655,  1656,    83,    84,   116,    86,    87,    88,    89,
     633,    91,   623,   636,     8,   148,   627,    86,   282,   129,
     100,   129,   116,   634,   172,   105,    20,   107,   129,   208,
     257,   111,   129,   149,   318,   115,   129,   117,   230,   315,
     321,   116,   318,   282,   124,  1835,  1836,   180,   128,    15,
     619,   116,   132,   794,   134,   116,   149,   126,   129,   116,
     116,   141,   142,   129,  2111,   145,   146,   177,   137,   166,
     116,   151,   470,   153,   749,     7,    64,   157,   379,   129,
     129,   574,  2029,    15,   116,   462,   116,  1173,  2135,   129,
      41,   129,   284,  1492,     8,  1494,   165,  1496,   129,  1498,
     149,   129,   116,   295,   184,   678,   186,   676,   150,   246,
    1411,     3,   364,   365,   129,    37,  1834,   710,   370,   371,
     372,   373,   116,   375,   376,   828,  2176,   379,   803,   381,
     382,   383,   384,    15,    26,   387,   839,   257,   390,  1833,
     392,  1593,  1551,  1552,  1608,   397,   257,  1768,   400,   737,
     402,  1267,   404,   856,     8,  1768,   408,   409,   410,   411,
     783,  1768,   785,   257,   958,   417,  1755,   419,   420,  1768,
     422,  1768,   971,   784,   973,  1768,   428,   429,     8,  1768,
    1755,   980,   257,   435,   436,  1774,  1768,   439,     8,   258,
    1831,   894,   257,  1768,   446,     8,   257,   449,   207,  1774,
     257,   257,   116,   796,   987,   908,   254,   129,   408,   461,
     169,   257,   464,  1172,  1403,   257,  1075,  1171,   470,   471,
     472,   473,   773,   475,   476,   257,  1160,   257,   237,   479,
     482,   483,   484,   485,   486,  1424,   488,   825,     3,   491,
    1268,   493,   494,   257,     8,   497,   623,   129,   500,   208,
     627,     5,   504,  2043,  2044,     9,   987,   634,   209,   560,
     665,    26,   116,   257,  1067,  1541,  1542,  2343,    15,   570,
     571,   572,   573,    64,    23,  1459,     8,   228,     8,     8,
    1308,   533,  2332,    37,   534,    15,   116,   191,    37,   539,
     540,   541,    15,   996,     8,   904,   116,     8,  1001,    15,
       7,     8,   554,   116,   208,   557,   558,   559,   560,  1341,
    1342,  1343,   562,   565,   566,   395,  1943,   569,   570,   571,
     572,   573,  2040,   282,  1932,   577,   578,  2022,     8,  2022,
    2380,   191,    15,    15,     8,     3,   905,  2031,   129,  1042,
       8,  1140,     8,   257,     8,  1492,    15,  1494,   129,  1496,
     266,  1498,   116,  2007,    92,  1383,  1755,    37,   149,   660,
     551,   552,    18,   974,   975,   976,   977,   978,   149,  1768,
      26,   287,   563,   191,   745,  1774,  1825,   147,   148,  1778,
     129,  1830,   683,   952,   116,    16,    17,   116,    95,   247,
     208,   643,   644,   645,   646,   647,   648,   649,     8,   129,
     652,   651,   116,   257,    15,   116,  1870,   784,   660,     8,
     180,   149,  2066,   129,     3,    15,  1825,   124,   498,   669,
       3,     5,   128,   257,    23,     9,   678,   257,   288,   681,
    2148,   683,    21,   116,    15,    18,   841,   257,    37,   299,
     845,     8,   116,     8,   257,   850,   129,   129,   853,   854,
     116,   157,   116,    37,   706,  1024,   128,    23,     5,     7,
     129,    92,     9,   201,   282,  1034,  1281,   285,     8,    16,
      17,    37,    37,     8,    21,     8,    23,     3,   779,   731,
    2134,   733,     8,     8,   736,   157,    21,  1409,   195,     8,
      37,  1425,  1426,   257,     8,   202,   746,   749,  1281,  1500,
    1501,  1502,    21,  1504,  1505,     8,   758,    21,   913,   759,
     915,   217,     7,     8,    63,   767,   766,   769,   149,    68,
       7,     8,   774,   824,   776,   257,   827,   779,   257,  1328,
    1329,  1330,  1331,  1332,  2426,  2427,     8,     7,     8,  2241,
     792,    90,    91,   257,     5,  1248,   257,  2439,     9,    21,
    1281,   803,  1283,   147,   148,    16,    17,   809,  1341,  1342,
    1343,  1589,    23,  1266,  1596,  1597,  1598,   252,     5,     8,
     201,   256,   824,  2200,   257,   827,    37,     3,    15,     8,
    2029,   833,   832,   257,   442,  1519,   180,  1521,     8,    15,
    2266,   257,    21,   257,     8,   144,    43,   974,   975,   976,
     977,   978,  1630,     8,     5,   154,     5,    21,  1755,  2263,
    1341,  1342,  1343,   863,    15,     8,    21,    16,    17,   477,
      67,  1768,     5,    22,     7,    24,  2280,  1774,    21,   487,
       8,  1778,   884,   885,    33,    82,    35,  2264,    37,   191,
      87,    88,   194,    21,     5,     8,     8,    94,   900,     8,
       8,   200,  1240,     8,    15,    16,    17,  2262,    21,    21,
       5,   252,    21,    21,     9,   256,    27,     8,    89,     3,
     922,    16,    17,   923,     7,    36,    21,    84,    23,  2390,
      21,    15,  2146,     8,     8,     8,   544,   545,   546,   547,
     548,  2402,    37,  1872,  1397,   886,    21,    21,    21,  1878,
       3,   122,     8,    64,  1820,  1821,  1822,  1823,  1824,  1404,
     901,  1406,    15,    41,  2341,  1820,  1821,  1822,  1823,  1824,
     314,   315,  1808,     8,   318,   319,     8,     8,  1392,     8,
    1394,    92,     8,  2338,   155,    84,    21,   595,   596,   597,
      21,   599,    21,    71,     8,    21,  1315,     8,   606,     8,
    1317,     8,  1321,  1005,     8,  1677,  1006,    21,  2059,  1011,
     159,     8,   620,   162,   185,  1017,     8,    21,   129,  1703,
       3,    15,     8,     8,    21,    16,    17,  1182,  1030,    21,
      21,   228,    15,  1188,   191,    21,    21,  1192,   149,  1194,
    1195,  1196,     8,  1198,  1588,  1200,  1363,   218,     8,   843,
     844,   208,   846,  1055,   662,    21,    15,   135,  1060,  1376,
      44,    21,   259,  1596,  1597,  1598,     3,     8,   149,   677,
    1389,    15,   902,     3,  1076,    22,  1854,    24,    15,  1402,
      21,   252,     8,  1083,   425,    15,    33,     8,    35,  1091,
     201,   169,   191,     8,  1872,    21,     8,   705,   247,     8,
    1878,     8,  1880,    87,   712,     8,   303,     8,   265,   208,
     718,   719,   453,   191,    21,  1596,  1597,  1598,    21,   460,
      21,   462,     8,     8,     8,   282,  1126,   191,   285,     7,
     208,   209,   289,   290,  1434,   119,    21,    21,    16,    17,
       8,   298,   299,   221,   208,   223,   224,   304,   226,     8,
       8,   229,  1605,    21,     8,   763,   305,   306,   307,   143,
       8,   145,    21,     5,     8,     8,   265,     9,   316,   317,
    1170,     8,  1002,    21,    16,    17,    22,    21,    24,     8,
       8,  1481,   129,   282,    21,     8,   285,    33,     8,    35,
     289,    15,    21,    21,   178,    37,     8,  2248,    21,   183,
     299,    21,    15,   187,   282,   304,     8,   191,    15,    21,
     194,   158,   159,  1213,   161,   162,  1669,    15,   282,    21,
    1271,   285,  1377,    16,    17,  1225,   290,   149,   836,   837,
    1230,  1592,   216,  1233,   298,  1235,  1236,  1237,     7,  1241,
    1242,     8,   320,     8,     8,   192,   230,    15,  1717,     5,
    1719,  1720,   236,     9,    21,  2194,    21,    21,     8,     8,
      16,    17,  1731,  1265,  1583,    21,     8,    23,    15,  1271,
       8,    21,  1741,  1275,  1743,    15,     8,     8,     8,    21,
      63,    37,   623,    21,     8,    68,   627,   234,  1607,    21,
    1609,    21,     8,   634,  1551,  1552,  1451,    21,   639,  1852,
     247,     8,  1621,   243,   244,    21,  1625,    90,    91,     8,
    1859,     8,   158,   159,    21,   161,   162,  1640,   254,    15,
     256,   257,    21,    15,    21,   933,   934,   935,   936,   937,
     938,   939,   940,   941,   942,   943,   944,   945,   946,   947,
     948,   949,   950,   951,  1346,    15,   192,     5,    15,     7,
     958,    15,    10,     8,    15,   963,    14,    15,    16,    17,
       8,   144,   970,     5,   972,  2143,    21,     9,     8,    27,
      15,   154,     5,    21,    16,    17,    34,    37,    36,   987,
       8,    21,    15,    16,    17,     8,     8,   124,   234,  1391,
    1392,  2169,  1394,    21,    27,    37,     8,     8,    21,    21,
    1402,   247,  1404,    36,  1406,  1013,    64,  1409,     8,    21,
      21,  1019,    15,     5,    15,     8,    15,   200,    10,  1249,
       8,    21,    14,    15,    16,    17,     8,  1035,    21,   982,
     983,    64,     8,    21,    92,    27,     8,  2376,  1440,    21,
      15,     8,    34,   784,    36,    21,    15,  1449,   231,    21,
      15,     8,    15,  1455,    21,  2422,  2423,  1457,     7,    92,
      15,   244,    15,  1465,    21,  1592,  2045,  2046,  2047,  2318,
    2319,   129,    64,     5,   851,   852,  1476,     9,  1478,    15,
    1482,    15,    15,    15,    16,    17,  1596,  1597,  1598,    15,
     124,   149,     3,   239,    15,    27,   129,    15,   246,    21,
      92,   246,    26,  1503,    36,     8,     7,    15,    15,    15,
       8,  1119,  2196,   240,  1514,    15,   149,  1517,     8,    15,
     861,   862,    15,   175,   149,     8,    15,     8,     8,  1531,
    1138,    15,    64,     8,     8,    26,  1536,   129,  1538,    15,
       5,     7,    62,   201,     9,    10,    15,    15,     8,    14,
      15,    16,    17,  1161,  1162,  1163,  1873,   149,    21,  1561,
      92,     8,    27,    15,    16,    17,   287,    15,   201,    34,
       8,    36,  1574,   326,   166,    27,  1876,     8,  2262,     8,
      15,  2265,  2266,   213,    36,     8,    64,     9,   129,    21,
       9,  1593,     8,     8,  1596,  1597,  1598,   129,     8,    64,
      67,    15,    16,    17,  1606,     8,    15,    37,    15,   201,
      15,  2164,    64,    27,    15,    15,    15,   149,  1943,   398,
      15,    15,    36,     8,    63,   129,     7,    92,    26,    68,
    1238,  2315,    15,   974,   975,   976,   977,   978,  1640,     7,
      92,   982,   983,    21,    21,    59,    21,    18,    37,     7,
      64,    90,    91,  2337,  2338,    15,    26,     7,  1660,     8,
    1268,    15,    15,    26,   129,     8,     8,     7,  1009,   201,
      21,    15,  1280,    21,    15,  1677,    15,   129,    92,    15,
      15,    15,     8,    21,   149,   124,    15,     5,    21,    62,
      15,  1032,    15,    15,    15,  2111,    15,   149,  2382,    15,
    1308,  2020,    15,     8,    21,   144,     8,     8,     8,  1711,
    1712,  2030,  1320,     8,     7,   154,    44,    15,    15,    15,
     255,   166,   239,   208,    16,    15,    15,    21,    15,  1070,
     509,     8,   511,    21,  1736,   149,   201,     7,   334,   518,
     519,   520,    15,    15,   315,   524,   525,   526,   527,   201,
     529,   530,   335,   425,     7,     5,  2186,  2187,   246,    87,
     246,   200,     8,  1371,  1372,    93,    15,   246,    15,   246,
      21,     8,     7,   246,     8,     8,    45,    46,  1386,    48,
      49,   453,    21,    21,    53,  1393,    26,   201,   460,    21,
      21,   119,    61,    15,   233,  1403,   468,    66,    21,   173,
      69,  1409,    15,  1411,    15,   244,   255,     8,    77,     7,
      79,    21,    81,    15,    71,   143,  1424,   145,    15,    18,
     208,     8,    15,    15,    15,    15,    15,    21,     5,  1437,
       8,  1833,  1834,  1835,  1836,   104,    21,  2262,    21,  2264,
    1448,    21,    21,    15,  1846,    15,   115,    21,    21,  2166,
     178,    15,    15,  1461,     7,   183,    21,     9,  1466,   187,
    1468,    20,     7,   191,    26,    21,   194,     5,    26,    15,
     139,    21,    10,  1875,    21,     5,    14,    15,    16,    17,
      10,    21,    21,   152,    14,    15,    16,    17,   216,    27,
      21,  1891,    15,    26,    18,     8,    34,    27,    36,    15,
      15,   170,   230,   575,    34,    15,    36,   176,   236,    21,
      40,     8,  1912,    15,    21,   184,    21,   186,    26,   188,
      21,   190,   254,    15,     8,  1927,    64,   132,   197,  1931,
      21,  1933,     7,     7,    64,    21,    21,    37,  1546,     7,
       7,  1943,    21,    21,   255,   214,   215,  1949,  1950,    15,
      15,    15,    15,    15,    92,    15,  1956,    15,    15,    15,
      15,     7,    92,   232,     8,  1965,     8,   639,    21,     7,
     239,    21,     8,     7,    21,    15,     7,     7,    15,  1587,
    1588,  1589,    21,  1983,   253,    78,   333,   256,     8,     7,
       7,   129,    21,    15,    15,  1336,    21,     8,    17,   129,
      15,    17,  2002,     7,     7,    15,     7,   128,   885,   218,
    1242,   149,  1620,   893,  1929,  1623,  1805,  1536,   797,   149,
    1174,  1079,  1540,  1631,   568,     5,  2143,     7,   166,  2031,
      10,  1806,   579,   576,    14,    15,    16,    17,  2040,   696,
    2042,  2043,  2044,  2045,  2046,  2047,  1273,    27,   922,  1570,
    2148,  2042,   922,  1825,    34,  1663,    36,  1665,     5,   731,
    1833,  2022,     9,   201,  1465,  1678,  1143,  1449,    15,    16,
      17,   201,  2093,  1927,  2074,  2113,  1950,   749,  1035,  1386,
      27,  1015,  1077,  1365,    64,  1651,  1653,    75,  1854,    36,
     762,  2428,   453,  1872,  1878,   697,  1409,   777,   770,   771,
    1441,   242,  1372,   775,  1024,   242,   242,   242,  1589,  2111,
    2112,  2113,    92,     5,  1592,   987,   643,    64,    10,  1091,
     823,  1060,    14,    15,    16,    17,  1163,   646,  2195,   645,
    1388,   803,   647,  1390,   648,    27,  2073,  2248,  2380,   811,
    1931,   792,    34,  1484,    36,    92,  2148,  1003,  1005,   129,
    2356,  1076,  1875,  1017,  1030,  1446,  2299,  1914,  2261,  1500,
    1501,  1502,  2382,  1504,  1505,  2404,  2424,  1508,   840,   149,
     842,  2426,    64,  2203,  1703,  1516,  1463,  1426,  1934,   494,
     652,   747,   129,  1880,  2186,  2187,   406,   373,  1514,   861,
     862,  1799,  1800,  2195,  2176,  1938,     5,  1755,  1774,  1807,
      92,    10,   149,  1730,     5,    14,    15,    16,    17,    10,
    1735,  1768,  1963,    14,    15,    16,    17,  1778,    27,   166,
    1962,   201,  2227,  1213,  1225,    34,    27,    36,  1983,    -1,
    1230,  1233,    -1,    34,    -1,    36,    -1,   129,    -1,    -1,
    1848,    -1,    -1,    -1,    -1,    -1,  1854,    -1,    -1,    -1,
    2252,  1592,  1593,    -1,   201,    64,    -1,   149,    -1,    -1,
    2262,    -1,  2264,    64,  1043,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1881,    -1,  1054,  2276,    -1,    -1,    -1,
      -1,    -1,  1890,    92,   956,   957,  2288,  2287,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1907,
    1908,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   201,
     982,   983,    -1,  1654,  1655,  1656,    -1,    -1,  2318,  2319,
     129,    -1,    -1,    -1,    -1,    -1,  1934,    -1,   129,    -1,
      -1,    -1,    -1,    -1,  1942,    -1,    -1,  1009,    -1,    -1,
     149,    -1,    -1,  1951,    -1,    -1,    -1,    -1,   149,    -1,
      -1,    -1,    -1,    -1,  2356,    -1,  2358,    -1,    -1,  1967,
    1032,  1969,    -1,    -1,    -1,    -1,    -1,    -1,  1147,    -1,
      -1,    -1,    -1,    45,    46,    -1,    48,    49,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,   201,    -1,    66,    -1,    -1,    69,  1070,    -1,
     201,    -1,  1181,    -1,    -1,    77,  2406,    79,  1187,    81,
      -1,  2411,  1191,    -1,  1193,    -1,    -1,    -1,  1197,    -1,
    1199,    -1,    -1,    -1,  2424,    -1,  2426,  2427,     7,    -1,
      -1,    10,   104,    -1,    -1,    14,    15,    16,    17,  2439,
      -1,    -1,    -1,   115,    -1,    -1,  2054,    -1,    27,    -1,
      -1,  2059,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,
      -1,     5,    -1,    -1,  2072,  2073,    10,   139,    -1,  2077,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,  2087,
     152,    -1,    -1,    27,  2092,    64,    -1,    -1,  1160,    -1,
      34,    -1,    36,    -1,    -1,    -1,    -1,    -1,   170,    -1,
      -1,    -1,    -1,    -1,   176,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   184,    92,   186,    -1,   188,    -1,   190,    -1,
      64,    -1,    -1,    -1,    -1,   197,    -1,    -1,    -1,     5,
      -1,  1872,    -1,     9,    -1,  2143,    -1,  1878,    -1,    -1,
      16,    17,   214,   215,    -1,    -1,    22,    23,    92,    25,
     129,    -1,    28,    29,    30,    31,    32,    -1,    -1,    35,
     232,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,  2179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   253,    -1,    -1,   256,   129,  2194,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1272,    -1,    -1,    -1,    -1,   149,    -1,    -1,     7,    -1,
      -1,    10,    -1,    -1,    -1,    14,    15,    16,    17,    -1,
    1399,    -1,   201,    -1,     7,    -1,    -1,    10,    27,    -1,
      -1,    14,    15,    16,    17,    34,    -1,    36,    -1,  2247,
    2248,    -1,    -1,  2251,    27,  2253,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    36,    -1,    -1,    -1,   201,    -1,    -1,
      -1,  2269,  2270,  2271,  1336,    64,  2007,    -1,  1447,    -1,
      -1,    -1,     5,  2281,    -1,    -1,     9,    -1,  2286,    78,
      -1,    64,    -1,    16,    17,    -1,   607,    -1,    -1,    22,
      23,  2299,    25,    92,    -1,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,  1487,    92,
      -1,  1490,    -1,    -1,  1493,    -1,  1495,    -1,  1497,    -1,
    1499,    -1,    -1,  2331,  2332,  2066,    -1,    -1,    -1,    -1,
     129,    -1,  1404,    -1,  1406,  2343,    -1,    -1,  2346,    -1,
    2348,    -1,    -1,    -1,    -1,    -1,   129,    -1,    -1,    -1,
     149,    -1,    -1,  1425,  1426,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1435,    -1,    -1,   149,    -1,  2376,  1441,
      -1,  1443,  2380,    -1,  1446,    -1,  2384,    -1,    -1,    -1,
    2388,    -1,  2390,    -1,    -1,    -1,  1458,    -1,    -1,    -1,
    1462,  1463,  2133,  2134,  2402,  2403,  2404,    -1,    -1,    -1,
      -1,    -1,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1484,    -1,    -1,    -1,    -1,    -1,   201,  1491,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1500,  1501,
    1502,    -1,  1504,  1505,    -1,   756,  1508,    -1,    -1,   760,
      -1,    -1,    -1,     7,  1516,    -1,    10,  1519,  1520,  1521,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,     7,    -1,
      -1,    10,    -1,    27,    -1,    14,    15,    16,    17,    -1,
      34,    -1,    36,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    34,   807,    36,    -1,  1561,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   819,    -1,
      64,    -1,    -1,    -1,     7,    -1,    -1,    10,    -1,    -1,
      -1,    14,    15,    16,    17,    64,    -1,    -1,    -1,    -1,
      -1,  1593,  2263,    -1,    27,    -1,    -1,    -1,    92,    -1,
      -1,    34,    -1,    36,    -1,    -1,    -1,    -1,    -1,  2280,
      -1,    -1,    -1,    92,    -1,  2286,    -1,    -1,  1727,    -1,
      -1,    -1,    -1,  1732,    -1,    -1,    -1,   878,   879,   880,
     881,    64,   883,    -1,    -1,   129,  1745,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,    -1,  1654,  1655,  1656,   149,    -1,    -1,  1767,    92,
      -1,    -1,    -1,    -1,  1773,    -1,    -1,    -1,  1777,    -1,
     149,    -1,    -1,    -1,    -1,    -1,   927,    -1,   929,   930,
     931,   932,    -1,    -1,    -1,     7,    -1,    -1,    10,    -1,
      -1,    -1,    14,    15,    16,    17,   129,    -1,    -1,    -1,
      -1,  1703,    -1,    -1,    -1,    27,    -1,   201,    -1,    -1,
      -1,    -1,    34,    -1,    36,    -1,   149,    -1,     7,    -1,
      -1,    10,   201,    -1,    -1,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   988,    27,    -1,
      -1,    -1,    64,    -1,    -1,    34,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1010,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   201,  1020,
      92,    -1,    10,    -1,    -1,    64,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
    1041,    -1,    -1,    -1,    -1,    -1,    34,    -1,    36,    -1,
      -1,    -1,    -1,    92,    -1,    -1,  1057,   129,    -1,    -1,
    1061,  1062,    -1,    -1,    -1,    -1,    -1,    -1,  1820,  1821,
    1822,  1823,  1824,    -1,    -1,    -1,    64,   149,    -1,    -1,
      -1,  1940,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,    -1,    -1,    -1,  1953,    -1,    -1,    -1,    -1,  1958,
      -1,    -1,  1961,    -1,    92,    -1,    -1,    -1,    -1,    -1,
     149,    -1,  1971,    -1,  1973,    -1,  1975,  1118,  1977,    -1,
    1872,    -1,    -1,    -1,    -1,    -1,  1878,    10,    -1,   201,
      -1,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,   129,    -1,    -1,    27,    -1,     5,    -1,    -1,    -1,
       9,    34,    -1,    36,    -1,    -1,    -1,    16,    17,  1911,
      -1,   149,   201,    -1,    23,    -1,    25,    -1,    -1,    28,
      29,    30,    31,    32,    -1,    -1,  1177,  1178,    37,    -1,
    1932,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1943,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,     7,    -1,     9,    10,    92,
      -1,  1963,    -1,   201,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,    -1,     5,
      -1,    -1,    -1,     9,    -1,  2007,  2008,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,   149,    23,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    32,    -1,    -1,  2031,
      -1,    37,    -1,  1284,  1285,  1286,  1287,  1288,  1289,  1290,
    1291,  1292,  1293,  1294,  1295,  1296,  1297,  1298,  1299,  1300,
    1301,  1302,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2063,    -1,    -1,  2066,    -1,  2068,  1318,   201,    -1,
      -1,    -1,    -1,     5,  1325,    -1,  1327,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,  1337,    -1,    -1,    -1,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
       5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,  1370,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,  2133,  2134,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    38,     5,    -1,     7,    -1,     9,    10,
      -1,  2260,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,  1438,     8,     9,
      10,    -1,    -1,    -1,  2196,    -1,    16,    17,  2200,    -1,
      -1,  1452,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,     8,
       9,    10,  1473,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2262,  2263,  2264,  2265,  2266,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1527,    -1,  2280,     5,
      -1,    -1,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,  1545,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,  2315,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,  1578,    -1,    -1,
       9,    10,    -1,    -1,  1585,  2337,  2338,    16,    17,  2341,
    1591,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,     5,  1616,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,  1628,    -1,    -1,
    2382,    22,    23,    24,    25,  1636,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,  1646,    37,    38,  1649,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1664,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1675,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    -1,    19,    -1,    21,  1689,    23,
      24,    -1,    26,    -1,  1695,    -1,    30,    -1,    32,    33,
    1701,    -1,    36,    37,    38,    -1,    40,    -1,    42,    43,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    60,    61,    -1,    -1,
      64,    65,    66,    -1,    68,    -1,    70,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,
      94,    -1,    96,    97,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,   106,    -1,    -1,   109,   110,    -1,   112,   113,
     114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,   123,
      -1,   125,   126,   127,    -1,   129,   130,    -1,    -1,   133,
      -1,   135,   136,   137,   138,   139,   140,    -1,    -1,    -1,
    1811,    -1,    -1,   147,   148,   149,    -1,    -1,    -1,    -1,
     154,   155,   156,    -1,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
      -1,   185,    -1,   187,  1855,   189,    -1,   191,   192,   193,
      -1,    -1,    -1,    -1,    -1,   199,   200,   201,   202,   203,
      -1,    -1,    -1,    -1,    -1,    -1,  1877,    -1,  1879,    -1,
      -1,    -1,  1883,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1906,     5,    -1,  1909,    -1,
       9,    10,    -1,    -1,    -1,    -1,   250,    16,    17,   253,
      -1,   255,    21,    22,    23,    24,    25,    -1,  1929,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
       5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,    -1,     9,    10,    -1,  2010,
    2011,    -1,    -1,    16,    17,    -1,    -1,  2018,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,  2049,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,  2070,
      -1,     5,    -1,    -1,  2075,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,  2085,  2086,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    -1,    -1,  2116,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,  2126,  2127,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2158,    -1,  2160,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,  2170,
      -1,     9,    10,    -1,  2175,    -1,    -1,  2178,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,  2190,
      28,    29,    30,    31,    32,    33,    -1,    35,     5,    37,
      38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,
     584,   585,    16,    17,    -1,    -1,  2257,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2292,    -1,  2294,    -1,    -1,    -1,  2298,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2310,
    2311,    -1,  2313,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,  2323,  2324,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2357,    -1,  2359,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,
    2371,  2372,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2395,    -1,    -1,    -1,  2399,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,  2409,    48,
      49,    50,    51,    52,    53,    -1,    -1,    56,    57,    -1,
      -1,    -1,    61,    62,    63,    -1,    65,    66,    67,    68,
      69,    70,    -1,    72,    73,    74,    75,    76,    77,    -1,
      79,    80,    81,    82,    83,    84,    -1,    -1,    87,    88,
      89,    90,    91,    -1,    -1,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,    -1,   117,    -1,
     119,   120,    -1,   122,   123,   124,    -1,    -1,   127,    -1,
      -1,   130,   131,    -1,   133,   134,   135,   136,    -1,   138,
     139,   140,   141,   142,   143,   144,   145,   146,    -1,    -1,
      -1,    -1,    -1,   152,   153,   154,   155,    -1,    -1,    -1,
      -1,   160,    -1,    -1,   163,   164,    -1,    -1,   167,   168,
      -1,   170,    -1,    -1,    -1,   174,    -1,   176,    -1,   178,
      -1,    -1,    -1,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,    -1,   193,   194,   195,    -1,   197,    -1,
     199,   200,    -1,   202,    -1,   204,   205,   206,   207,    -1,
      -1,   210,   211,   212,    -1,   214,   215,   216,    -1,   218,
     219,   220,    -1,   222,    -1,   224,   225,   226,   227,   228,
      -1,   230,    -1,   232,   233,    -1,    -1,   236,   237,   238,
      -1,    -1,   241,   242,    -1,   244,   245,    -1,   247,   248,
      -1,    -1,    -1,   252,   253,    -1,    -1,   256,    -1,    -1,
     259,    -1,    -1,    -1,   263,   264,    -1,    -1,   267,   268,
     269,    -1,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,    -1,   283,    -1,    -1,   286,    -1,    -1,
      -1,   290,   291,   292,   293,   294,    -1,   296,   297,    -1,
      -1,   300,   301,   302,   303,    -1,    -1,    -1,    -1,   308,
     309,   310,   311,   312,   313,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   322,   323,   324,   325,    -1,   327,   328,
     329,   330,   331,   332,     5,    -1,    -1,   336,     9,    10,
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
       0,   340,     0,     1,   150,   257,   341,   342,   116,     6,
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
     330,   331,   332,   336,   343,   345,   348,   360,   361,   365,
     366,   367,   373,   374,   375,   376,   378,   379,   381,   383,
     384,   385,   386,   393,   394,   395,   396,   397,   398,   402,
     403,   404,   408,   409,   447,   449,   462,   505,   506,   508,
     509,   515,   516,   517,   518,   525,   526,   527,   528,   530,
     533,   537,   538,   539,   540,   541,   547,   548,   549,   560,
     561,   562,   564,   567,   570,   575,   576,   578,   580,   582,
     585,   586,   610,   611,   622,   623,   624,   625,   630,   633,
     636,   639,   640,   688,   689,   690,   691,   692,   693,   694,
     695,   701,   703,   705,   707,   709,   710,   711,   712,   713,
     716,   718,   719,   720,   723,   724,   728,   729,   731,   732,
     733,   734,   735,   736,   737,   740,   745,   750,   752,   753,
     754,   755,   756,   757,   758,   759,   776,   779,   780,   781,
     782,   788,   791,   796,   797,   798,   801,   802,   803,   804,
     805,   806,   807,   808,   809,   810,   811,   812,   813,   814,
     815,   820,   821,   822,   823,   824,   834,   835,   836,   837,
     838,   839,   840,   841,    15,   472,   472,   534,   534,   534,
     534,   534,   472,   534,   534,   344,   534,   534,   534,   472,
     534,   472,   534,   534,   472,   534,   534,   534,   471,   534,
     472,   534,   534,     7,    15,   473,    15,   472,   593,   534,
     472,   357,   534,   534,   534,   534,   534,   534,   534,   534,
     534,   534,   129,   350,   514,   514,   534,   534,   534,   472,
     534,   350,   534,   472,   472,   534,   534,   471,   344,   472,
     472,    64,   356,   534,   534,   472,   472,   472,   472,   472,
     472,   472,   534,   411,   534,   534,   534,   350,   448,   344,
     472,   534,   534,   534,   472,   534,   472,   534,   534,   472,
     534,   534,   534,   472,   344,   472,   357,   534,   534,   357,
     534,   472,   534,   534,   534,   472,   534,   534,   472,   534,
     472,   534,   534,   534,   534,   534,   534,    15,   472,   571,
     472,   344,   472,   472,   534,   534,   534,    15,     8,   472,
     472,   534,   534,   534,   472,   534,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   534,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   534,   534,   534,   534,   534,
     534,   472,   534,   472,   534,   534,   534,   534,   534,    15,
      15,    15,   350,   853,   534,   534,   534,   534,   534,   257,
     559,   124,   233,   381,    15,   353,   559,     8,     8,     8,
       8,     7,     8,   124,   345,   368,     8,   350,   382,     8,
       8,     8,     8,     8,   529,     8,   529,     8,     8,     8,
       8,   529,   559,     7,   218,   252,   506,   508,   517,   518,
     239,   526,   526,    10,    14,    15,    16,    17,    27,    34,
      36,    64,    92,   149,   201,   350,   362,   478,   479,   481,
     482,   483,   484,   490,   491,   492,   493,   494,   497,    15,
     534,     5,     9,    15,    16,    17,   129,   480,   482,   490,
     543,   557,   558,   534,    15,   543,   534,     5,   542,   543,
     558,   543,     8,     8,     8,     8,     8,     8,     8,     8,
       7,     8,     8,     5,     7,   350,   620,   621,   350,   613,
     473,    15,    15,   149,   461,   350,   350,   721,   722,     8,
     350,   637,   638,   722,   350,   352,   350,    15,   510,   555,
      23,    37,   350,   400,   401,    15,   350,   583,   350,   652,
     652,   350,   634,   635,   350,   513,   410,    15,   350,   563,
     149,   727,   513,     7,   456,   457,   472,   594,   595,   350,
     589,   595,    15,   535,   350,   565,   566,   513,    15,    15,
     513,   727,   514,   513,   513,   513,   513,   350,   513,   353,
     513,    15,   405,   473,   481,   482,    15,   347,   350,   350,
     631,   632,   463,   464,   465,   466,     8,   653,   717,    15,
     350,   577,   350,   568,   569,    15,    15,   350,   473,    15,
     478,   730,    15,    15,   350,   704,   706,     8,   350,    37,
     399,    15,   482,   483,   473,    15,    15,   535,   461,   473,
     482,   350,   696,     5,    15,   557,   558,   473,   350,   351,
     473,   556,    15,   481,   614,   615,   589,   593,   350,   581,
     350,   676,   676,    15,   350,   579,   696,   478,   489,   473,
     357,    15,   350,   682,   682,   682,   682,   682,     7,   478,
     572,   573,   350,   574,   473,   346,   350,   473,   350,   702,
     704,   350,   472,   473,   350,   450,    15,    15,   556,   350,
      15,   595,    15,   595,   595,   595,   595,   762,   818,   595,
     595,   595,   595,   595,   595,   762,   350,   357,   825,   826,
     827,    15,    15,    15,   357,   842,   843,   844,   845,   357,
     846,   847,   848,   849,   850,   357,   851,   852,   478,   478,
     478,   478,   477,   478,   344,   344,   124,     5,    21,   350,
     354,   355,   349,   357,   350,   350,   350,   401,     7,   357,
     344,   124,   350,   350,     5,    15,   388,   389,   350,   401,
     401,   401,   401,   400,   481,   399,   350,   350,   405,   412,
     413,   415,   416,   534,   534,   239,   391,   478,   479,   478,
     478,   478,   478,     5,     9,    16,    17,    22,    23,    24,
      25,    26,    28,    29,    30,    31,    32,    33,    35,    37,
      38,   362,    15,   246,     3,    15,   246,   246,    15,   487,
     488,    21,   531,   555,   489,     5,     9,   166,   544,   545,
     546,   557,    26,   557,     5,     9,    23,    37,   480,   556,
     557,   556,     8,    15,   482,   550,   551,    15,   478,   479,
     494,   552,   553,   554,   552,   563,   350,   577,   579,   581,
     583,   350,     7,   357,   702,     8,    21,   615,   401,   503,
     478,   240,   529,    15,   357,    15,   455,     8,   555,     7,
     478,   511,   512,   513,    15,   350,   455,   401,   460,   461,
       8,   412,   503,   455,    15,     8,    21,     5,     7,   458,
     459,   478,   350,     8,    21,     5,    58,    86,   126,   137,
     165,   258,   596,   592,   593,   175,   584,   478,   149,   524,
       8,   478,   478,   349,   350,   406,   407,   481,   486,   350,
      26,   350,   519,   520,   522,   353,     8,     8,    15,   231,
     381,   467,   357,     8,   717,   350,   481,   686,   696,   714,
     715,     8,    26,     5,     9,    16,    17,    22,    23,    24,
      25,    28,    29,    30,    31,    32,    33,    34,    35,    37,
      38,   362,   363,   364,   350,   357,   371,   481,   478,    15,
     357,   350,   350,   481,   481,   504,     8,   653,   708,   350,
     481,   641,   642,   350,   445,   446,   524,   401,    18,   556,
     557,   556,   377,   380,   620,   615,     7,   593,   595,   686,
     696,   697,   698,   400,   401,   439,   440,    62,   481,   741,
      15,    15,     7,     8,    21,   571,   401,   353,   401,   455,
       8,   651,   673,    21,   357,   350,     8,   478,   478,   455,
     481,   529,   783,   481,   287,   795,   795,   529,   792,   795,
      15,   529,   760,   529,   799,   760,   760,   529,   777,   529,
     789,   455,   147,   148,   180,   314,   315,   318,   319,   358,
     828,   829,   830,     8,    21,   482,   657,   831,    21,   831,
     357,   738,   739,   191,   208,     8,    21,    41,   209,   228,
       8,    21,   326,     8,    21,     8,     8,     8,     8,   350,
     346,   344,     8,    21,   213,   358,   455,    44,    87,    93,
     119,   143,   145,   178,   183,   187,   191,   194,   216,   230,
     236,   369,   370,   372,   350,   344,   472,   535,   555,   382,
     455,   529,   529,     8,    37,    15,   350,   418,   423,   357,
      15,   498,    21,     8,   478,   478,   478,   478,   478,   478,
     478,   478,   478,   478,   478,   478,   478,   478,   478,   478,
     478,   478,   478,   555,    64,   129,   474,   476,   555,   481,
     492,   495,    64,   495,   489,     8,    21,     5,   478,   532,
     546,     8,    21,     5,     9,   478,    21,   478,   557,   557,
     557,   557,   557,    21,   550,   550,     8,   478,   479,   553,
     554,     8,     8,     8,   455,   455,   472,    43,    67,    82,
      87,    88,    94,   228,   259,   303,   624,   621,   357,   481,
     484,   485,   501,    21,   350,    15,   477,    67,   456,   638,
     478,     7,     8,    21,   531,    37,     8,    21,   635,   481,
     484,   500,   502,   555,   725,   458,     7,   455,   595,    15,
      15,    15,    15,    15,    15,   584,   595,   350,    21,   536,
     566,    21,    21,    15,     8,    21,     8,   488,   482,     8,
     521,    26,   349,   632,   464,   129,   468,   469,   470,   386,
     169,   208,   282,   357,    15,     7,     8,    21,   569,    21,
      21,   147,   148,   180,    21,    18,    21,     7,   478,   496,
     175,   321,    37,     8,    21,   357,     8,    21,    26,     8,
      21,   536,   478,    21,   441,   442,   441,    21,     7,   595,
     584,    15,     7,     8,    21,     8,    15,    15,    26,   683,
     684,   686,   477,   478,   573,   357,     8,   673,     8,   651,
     382,   372,   359,    21,    21,    21,   595,   529,    21,   595,
     529,   819,   595,   529,   595,   529,   595,   529,   595,   529,
      15,    15,    15,    15,    15,    15,   357,   827,     8,    21,
      21,   182,   315,   318,     8,    21,    15,    15,   843,    15,
      15,    15,   847,   852,   357,   357,   357,   478,   353,   350,
     355,    15,   387,   388,   455,   472,    15,     7,     8,   350,
     455,    15,   492,     5,   390,   478,   546,   401,   481,   415,
      15,    16,    17,    27,    36,    59,    64,    92,   149,   201,
     414,   416,   426,   427,   428,   429,   430,   431,   432,   433,
     418,   423,   424,   425,    15,   419,   420,    62,   478,   552,
     479,   474,    21,     8,   475,   478,   496,   546,     7,   555,
     461,   478,   555,     8,   551,    21,     8,     8,     8,   479,
     554,   479,   554,   479,   554,   350,   255,    15,    15,     8,
      21,   461,   460,    21,     7,    21,   478,   511,    21,   461,
     529,     8,    21,   546,   726,     8,    21,   459,   478,   596,
     555,    15,   598,   350,   597,   597,   478,   597,   455,   595,
     239,   513,   477,   407,   407,   350,   478,   520,    21,   478,
     496,     8,    21,    16,    15,    15,    15,   477,   714,   715,
     473,   481,   746,     7,   478,     7,    21,    21,   350,   591,
     482,   481,   642,   595,   643,   478,   446,   529,     8,    47,
     177,   350,   444,   357,   612,   614,   584,     7,     7,   478,
     699,   700,   697,   698,   440,   478,     5,   598,   742,   743,
     749,   478,   608,     8,    21,    15,    21,    71,   208,   357,
     357,   473,   172,   350,   453,   454,   482,   191,   208,   282,
     285,   290,   298,   763,   764,   765,   772,   784,   785,   786,
     595,   266,   793,   794,   795,   595,    37,   481,   816,   817,
      84,   265,   289,   299,   304,   761,   763,   764,   765,   766,
     767,   768,   770,   771,   772,   595,   763,   764,   765,   766,
     767,   768,   770,   771,   772,   785,   786,   800,   595,   763,
     764,   765,   772,   778,   595,   763,   764,   790,   595,   831,
     831,   831,   357,   832,   833,   831,   831,   482,   739,   657,
     357,   677,   683,   697,   683,   334,   315,   335,   350,    18,
      26,   392,    15,   371,     7,   357,   387,   536,   536,   391,
       5,   478,   429,   430,   431,   434,   430,   432,   430,   432,
     246,   246,   246,   246,   246,     8,    37,   350,   417,   481,
       5,   419,   420,     8,    15,    16,    17,   149,   350,   417,
     421,   422,   435,   436,   437,   438,    15,   420,    15,    21,
     499,    21,    21,   488,   555,   478,   489,   532,   545,   557,
     522,   523,   479,   523,   523,   523,   455,   350,   616,   619,
     555,   474,   555,     8,    21,     7,   391,   478,   555,   478,
     555,   546,   609,   478,   599,   600,    21,    21,    21,    21,
       8,     8,   254,   507,   513,    21,   469,   470,   657,   657,
     657,    21,    21,   350,    15,    21,   478,     7,     7,   478,
     455,   173,     8,   647,   648,   649,   650,   651,   653,   654,
     655,   658,   659,   660,   673,   681,   522,   442,    15,    15,
     443,   255,     8,     7,     8,    21,    21,    21,     8,    21,
      21,   684,   685,    15,    15,   350,   350,   451,   452,    18,
       8,    26,   762,    15,   762,   762,    15,   595,   784,   762,
     595,   793,   350,     8,    21,    15,   762,    15,   762,    15,
     595,   761,   595,   800,   595,   778,   595,   790,    21,    21,
      21,   316,   317,     8,    21,    21,    21,    21,    22,    24,
      33,    35,   158,   159,   161,   162,   192,   234,   247,   678,
     679,   680,     8,    21,    21,    21,    21,    15,    15,    21,
     478,   478,   626,   627,    21,   370,   392,     5,   478,   382,
       8,    21,     8,   495,   495,   495,   495,   495,   426,     5,
      15,   416,   427,   420,   350,   417,   425,   435,   436,   436,
       8,    21,     7,    16,    17,     5,    37,     9,   435,   478,
      20,   488,   475,    21,    26,    21,    21,    21,    21,    15,
     474,    21,   485,   546,   461,   637,   473,   500,   546,   726,
     478,    21,     7,     8,    21,   478,   357,    15,    21,    21,
      21,     7,   747,   748,   749,   478,   478,     7,   481,   644,
     357,   649,    26,   444,    26,   363,   616,   614,   350,   587,
     588,   589,   590,   700,   743,   595,    78,   572,   350,   652,
     697,   674,    18,     8,   350,   454,   478,   595,   773,   357,
     595,   595,   818,   481,   816,   357,   478,   478,   595,   595,
     595,   595,   833,    15,    15,   357,   657,   481,     8,    21,
       7,    21,    21,   555,   434,   427,   555,   417,    26,    21,
     435,   422,   436,   436,   437,   437,   437,    21,   478,     5,
     478,   496,   617,   618,    21,   481,     8,   657,   481,     8,
     478,   600,   357,    21,   254,   478,     8,    21,   478,    15,
      41,   135,   191,   209,   221,   223,   224,   226,   229,   320,
     478,   443,    21,    21,    15,     8,   132,   744,    21,    21,
       7,    21,   676,   678,   350,   452,     5,    16,    17,    22,
      24,    33,    35,    37,   159,   162,   247,   305,   306,   307,
     775,    21,    94,   230,   284,   295,   787,    37,   191,   288,
     299,   769,    21,    21,   482,   657,   678,    21,    21,     7,
       7,   390,    21,   474,   421,   435,    21,     8,     8,    21,
     461,   546,   255,    15,    21,   748,     5,   478,   645,   646,
      15,   661,    15,    15,    15,    15,    15,   682,   682,    15,
      15,     8,   477,   588,   686,   687,    15,   697,   675,   675,
       7,     8,    21,   819,    21,    21,     8,     8,     7,   391,
      21,    21,   478,   618,   478,   350,   601,   602,   478,     8,
      21,   595,   661,   696,   714,   657,   696,   697,   686,   683,
     478,   478,   656,   478,    21,     8,   357,    21,     7,     8,
      21,   657,   774,   478,   478,   482,   357,   350,   628,   629,
      21,     8,    15,    21,   646,   148,   180,   662,     7,    21,
      21,     7,    21,    15,    21,    21,     8,    21,     8,   686,
      78,   677,   677,    21,    21,   333,     8,   478,    40,   478,
     603,   604,   749,     7,     7,   663,   664,   686,   714,   697,
     572,   478,   478,    21,    21,    21,    15,   629,   350,   605,
       8,    21,     8,    21,    15,    21,    21,    21,     8,   477,
      17,   606,   607,   604,   664,   478,   665,   666,    21,   478,
      21,   608,    17,     7,     8,    21,     8,   751,   608,   478,
     666,    15,   357,   357,   667,   668,   669,   670,   671,   182,
     318,   128,   157,   217,     8,    21,     7,     7,    15,   672,
     672,   672,   668,   357,   670,   671,   357,   671,   476,     7,
      21,   671
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
#line 765 "gram1.y"
    { (yyval.bf_node) = BFNULL; ;}
    break;

  case 3:
#line 767 "gram1.y"
    { (yyval.bf_node) = set_stat_list((yyvsp[(1) - (3)].bf_node),(yyvsp[(2) - (3)].bf_node)); ;}
    break;

  case 4:
#line 771 "gram1.y"
    { lastwasbranch = NO;  (yyval.bf_node) = BFNULL; ;}
    break;

  case 5:
#line 773 "gram1.y"
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
#line 787 "gram1.y"
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
#line 818 "gram1.y"
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
#line 827 "gram1.y"
    {
	      err("Unclassifiable statement", 10);
	      flline();
	      (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 9:
#line 833 "gram1.y"
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
#line 853 "gram1.y"
    { 
	      flline();	 needkwd = NO;	inioctl = NO;
/*!!!*/
              opt_kwd_ = NO; intonly = NO; opt_kwd_hedr = NO; opt_kwd_r = NO; as_op_kwd_= NO; optcorner = NO;
	      yyerrok; yyclearin;  (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 11:
#line 862 "gram1.y"
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
#line 878 "gram1.y"
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
#line 890 "gram1.y"
    {  PTR_BFND q = BFNULL;

	      (yyvsp[(3) - (3)].symbol)->variant = PROCEDURE_NAME;
	      (yyvsp[(3) - (3)].symbol)->decl = YES;   /* variable declaration has been seen. */
	      q = get_bfnd(fi,BLOCK_DATA, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
	      set_blobs(q, global_bfnd, NEW_GROUP1);
              add_scope_level(q, NO);
	    ;}
    break;

  case 14:
#line 900 "gram1.y"
    { 
              install_param_list((yyvsp[(3) - (4)].symbol), (yyvsp[(4) - (4)].symbol), LLNULL, PROCEDURE_NAME); 
	      /* if there is only a control end the control parent is not set */
              
	     ;}
    break;

  case 15:
#line 907 "gram1.y"
    { install_param_list((yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].symbol), LLNULL, PROCEDURE_NAME); 
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP) 
                   (yyvsp[(4) - (5)].symbol)->attr = (yyvsp[(4) - (5)].symbol)->attr | RECURSIVE_BIT;
              pred_bfnd->entry.Template.ll_ptr3 = (yyvsp[(1) - (5)].ll_node);
            ;}
    break;

  case 16:
#line 913 "gram1.y"
    {
              install_param_list((yyvsp[(3) - (5)].symbol), (yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].ll_node), FUNCTION_NAME);  
  	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(5) - (5)].ll_node);
            ;}
    break;

  case 17:
#line 918 "gram1.y"
    {
              install_param_list((yyvsp[(1) - (3)].symbol), (yyvsp[(2) - (3)].symbol), (yyvsp[(3) - (3)].ll_node), FUNCTION_NAME); 
	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
	    ;}
    break;

  case 18:
#line 923 "gram1.y"
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
#line 947 "gram1.y"
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
#line 973 "gram1.y"
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
#line 988 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, RECURSIVE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 22:
#line 990 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PURE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 23:
#line 992 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, ELEMENTAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 24:
#line 996 "gram1.y"
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
#line 1013 "gram1.y"
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
#line 1027 "gram1.y"
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
#line 1051 "gram1.y"
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
#line 1067 "gram1.y"
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
#line 1081 "gram1.y"
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
#line 1099 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 31:
#line 1101 "gram1.y"
    { PTR_SYMB s;
              s = make_scalar((yyvsp[(4) - (5)].hash_entry), TYNULL, LOCAL);
              (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 32:
#line 1108 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 33:
#line 1111 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_MAIN")); ;}
    break;

  case 34:
#line 1113 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry));
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
            ;}
    break;

  case 35:
#line 1119 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_BLOCK")); ;}
    break;

  case 36:
#line 1121 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry)); 
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
	    ;}
    break;

  case 37:
#line 1128 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 38:
#line 1130 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 39:
#line 1132 "gram1.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); ;}
    break;

  case 41:
#line 1137 "gram1.y"
    { (yyval.symbol) = set_id_list((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); ;}
    break;

  case 42:
#line 1141 "gram1.y"
    {
	      (yyval.symbol) = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, IO);
            ;}
    break;

  case 43:
#line 1145 "gram1.y"
    { (yyval.symbol) = make_scalar(look_up_sym("*"), TYNULL, IO); ;}
    break;

  case 44:
#line 1151 "gram1.y"
    { char *s;

	      s = copyn(yyleng+1, yytext);
	      s[yyleng] = '\0';
	      (yyval.charp) = s;
	    ;}
    break;

  case 45:
#line 1160 "gram1.y"
    { needkwd = 1; ;}
    break;

  case 46:
#line 1164 "gram1.y"
    { needkwd = NO; ;}
    break;

  case 47:
#line 1169 "gram1.y"
    { colon_flag = YES; ;}
    break;

  case 61:
#line 1190 "gram1.y"
    {
	      saveall = YES;
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 62:
#line 1195 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, (yyvsp[(4) - (4)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 63:
#line 1200 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL, SMNULL);
	      p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,FORMAT_STAT, SMNULL, p, LLNULL, LLNULL);
             ;}
    break;

  case 64:
#line 1207 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,PARAM_DECL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 77:
#line 1223 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, SMNULL, LLNULL, LLNULL, LLNULL); 
             /* add_scope_level($$, NO); */    
            ;}
    break;

  case 78:
#line 1227 "gram1.y"
    { PTR_SYMB s;

	      s = make_procedure((yyvsp[(3) - (3)].hash_entry), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 79:
#line 1235 "gram1.y"
    { PTR_SYMB s;

	      s = make_function((yyvsp[(4) - (5)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_OPERATOR, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 80:
#line 1243 "gram1.y"
    { PTR_SYMB s;


	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_ASSIGNMENT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 81:
#line 1252 "gram1.y"
    { parstate = INDCL;
              (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      /*process_interface($$);*/ /*podd 01.02.03*/
              /*delete_beyond_scope_level(pred_bfnd);*/
	    ;}
    break;

  case 82:
#line 1260 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 83:
#line 1264 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 84:
#line 1266 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 85:
#line 1270 "gram1.y"
    { (yyval.hash_entry) = look_up_op(PLUS); ;}
    break;

  case 86:
#line 1272 "gram1.y"
    { (yyval.hash_entry) = look_up_op(MINUS); ;}
    break;

  case 87:
#line 1274 "gram1.y"
    { (yyval.hash_entry) = look_up_op(ASTER); ;}
    break;

  case 88:
#line 1276 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DASTER); ;}
    break;

  case 89:
#line 1278 "gram1.y"
    { (yyval.hash_entry) = look_up_op(SLASH); ;}
    break;

  case 90:
#line 1280 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DSLASH); ;}
    break;

  case 91:
#line 1282 "gram1.y"
    { (yyval.hash_entry) = look_up_op(AND); ;}
    break;

  case 92:
#line 1284 "gram1.y"
    { (yyval.hash_entry) = look_up_op(OR); ;}
    break;

  case 93:
#line 1286 "gram1.y"
    { (yyval.hash_entry) = look_up_op(XOR); ;}
    break;

  case 94:
#line 1288 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NOT); ;}
    break;

  case 95:
#line 1290 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQ); ;}
    break;

  case 96:
#line 1292 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NE); ;}
    break;

  case 97:
#line 1294 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GT); ;}
    break;

  case 98:
#line 1296 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GE); ;}
    break;

  case 99:
#line 1298 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LT); ;}
    break;

  case 100:
#line 1300 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LE); ;}
    break;

  case 101:
#line 1302 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NEQV); ;}
    break;

  case 102:
#line 1304 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQV); ;}
    break;

  case 103:
#line 1309 "gram1.y"
    {
             PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, LLNULL, LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 104:
#line 1318 "gram1.y"
    { PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, (yyvsp[(5) - (7)].ll_node), LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 105:
#line 1328 "gram1.y"
    {
	     (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);
           ;}
    break;

  case 106:
#line 1336 "gram1.y"
    {
             (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);	
           ;}
    break;

  case 107:
#line 1346 "gram1.y"
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
#line 1367 "gram1.y"
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
#line 1386 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 110:
#line 1388 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 111:
#line 1390 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node); ;}
    break;

  case 112:
#line 1394 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 113:
#line 1396 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); ;}
    break;

  case 114:
#line 1400 "gram1.y"
    { type_options = type_options | PARAMETER_BIT; 
              (yyval.ll_node) = make_llnd(fi, PARAMETER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 115:
#line 1404 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 116:
#line 1406 "gram1.y"
    { type_options = type_options | ALLOCATABLE_BIT;
              (yyval.ll_node) = make_llnd(fi, ALLOCATABLE_OP, LLNULL, LLNULL, SMNULL);
	    ;}
    break;

  case 117:
#line 1410 "gram1.y"
    { type_options = type_options | DIMENSION_BIT;
	      attr_ndim = ndim;
	      attr_dims = (yyvsp[(2) - (2)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DIMENSION_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 118:
#line 1416 "gram1.y"
    { type_options = type_options | EXTERNAL_BIT;
              (yyval.ll_node) = make_llnd(fi, EXTERNAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 119:
#line 1420 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node); ;}
    break;

  case 120:
#line 1422 "gram1.y"
    { type_options = type_options | INTRINSIC_BIT;
              (yyval.ll_node) = make_llnd(fi, INTRINSIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 121:
#line 1426 "gram1.y"
    { type_options = type_options | OPTIONAL_BIT;
              (yyval.ll_node) = make_llnd(fi, OPTIONAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 122:
#line 1430 "gram1.y"
    { type_options = type_options | POINTER_BIT;
              (yyval.ll_node) = make_llnd(fi, POINTER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 123:
#line 1434 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, SAVE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 124:
#line 1438 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, STATIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 125:
#line 1442 "gram1.y"
    { type_options = type_options | TARGET_BIT; 
              (yyval.ll_node) = make_llnd(fi, TARGET_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 126:
#line 1448 "gram1.y"
    { type_options = type_options | IN_BIT;  type_opt = IN_BIT; 
              (yyval.ll_node) = make_llnd(fi, IN_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 127:
#line 1452 "gram1.y"
    { type_options = type_options | OUT_BIT;  type_opt = OUT_BIT; 
              (yyval.ll_node) = make_llnd(fi, OUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 128:
#line 1456 "gram1.y"
    { type_options = type_options | INOUT_BIT;  type_opt = INOUT_BIT;
              (yyval.ll_node) = make_llnd(fi, INOUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 129:
#line 1462 "gram1.y"
    { type_options = type_options | PUBLIC_BIT; 
              type_opt = PUBLIC_BIT;
              (yyval.ll_node) = make_llnd(fi, PUBLIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 130:
#line 1467 "gram1.y"
    { type_options =  type_options | PRIVATE_BIT;
               type_opt = PRIVATE_BIT;
              (yyval.ll_node) = make_llnd(fi, PRIVATE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 131:
#line 1474 "gram1.y"
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
#line 1485 "gram1.y"
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
#line 1498 "gram1.y"
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
#line 1509 "gram1.y"
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
#line 1522 "gram1.y"
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
#line 1532 "gram1.y"
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
#line 1545 "gram1.y"
    {
	      privateall = 1;
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 138:
#line 1550 "gram1.y"
    {
	      /*type_options = type_options | PRIVATE_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 139:
#line 1556 "gram1.y"
    {type_opt = PRIVATE_BIT;;}
    break;

  case 140:
#line 1560 "gram1.y"
    { 
	      (yyval.bf_node) = get_bfnd(fi, SEQUENCE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
            ;}
    break;

  case 141:
#line 1565 "gram1.y"
    {
	      /*saveall = YES;*/ /*14.03.03*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 142:
#line 1570 "gram1.y"
    {
	      /*type_options = type_options | PUBLIC_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 143:
#line 1576 "gram1.y"
    {type_opt = PUBLIC_BIT;;}
    break;

  case 144:
#line 1580 "gram1.y"
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
#line 1590 "gram1.y"
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
#line 1603 "gram1.y"
    {opt_kwd_hedr = YES;;}
    break;

  case 147:
#line 1608 "gram1.y"
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
#line 1627 "gram1.y"
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
#line 1653 "gram1.y"
    { (yyval.token) = ATT_GLOBAL; ;}
    break;

  case 150:
#line 1655 "gram1.y"
    { (yyval.token) = ATT_CLUSTER; ;}
    break;

  case 151:
#line 1667 "gram1.y"
    {
/*		  varleng = ($1<0 || $1==TYLONG ? 0 : typesize[$1]); */
		  vartype = (yyvsp[(1) - (1)].data_type);
		;}
    break;

  case 152:
#line 1674 "gram1.y"
    { (yyval.data_type) = global_int; ;}
    break;

  case 153:
#line 1675 "gram1.y"
    { (yyval.data_type) = global_float; ;}
    break;

  case 154:
#line 1676 "gram1.y"
    { (yyval.data_type) = global_complex; ;}
    break;

  case 155:
#line 1677 "gram1.y"
    { (yyval.data_type) = global_double; ;}
    break;

  case 156:
#line 1678 "gram1.y"
    { (yyval.data_type) = global_dcomplex; ;}
    break;

  case 157:
#line 1679 "gram1.y"
    { (yyval.data_type) = global_bool; ;}
    break;

  case 158:
#line 1680 "gram1.y"
    { (yyval.data_type) = global_string; ;}
    break;

  case 159:
#line 1685 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 160:
#line 1687 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 161:
#line 1691 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(3) - (5)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 162:
#line 1693 "gram1.y"
    { PTR_LLND l;

                 l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL); 
                 l->entry.string_val = (char *)"*";
                 (yyval.ll_node) = make_llnd(fi, LEN_OP, l,l, SMNULL);
                ;}
    break;

  case 163:
#line 1700 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(5) - (6)].ll_node), (yyvsp[(5) - (6)].ll_node), SMNULL);;}
    break;

  case 164:
#line 1704 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 165:
#line 1706 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 166:
#line 1708 "gram1.y"
    { /*$$ = make_llnd(fi, PAREN_OP, $2, LLNULL, SMNULL);*/  (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node);  ;}
    break;

  case 167:
#line 1716 "gram1.y"
    { if((yyvsp[(7) - (9)].ll_node)->variant==LENGTH_OP && (yyvsp[(3) - (9)].ll_node)->variant==(yyvsp[(7) - (9)].ll_node)->variant)
                (yyvsp[(7) - (9)].ll_node)->variant=KIND_OP;
                (yyval.ll_node) = make_llnd(fi, CONS, (yyvsp[(3) - (9)].ll_node), (yyvsp[(7) - (9)].ll_node), SMNULL); 
            ;}
    break;

  case 168:
#line 1723 "gram1.y"
    { if(vartype->variant == T_STRING)
                (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
              else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
            ;}
    break;

  case 169:
#line 1729 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 170:
#line 1735 "gram1.y"
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
#line 1744 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 172:
#line 1752 "gram1.y"
    {endioctl();;}
    break;

  case 173:
#line 1765 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 174:
#line 1767 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node); ;}
    break;

  case 175:
#line 1770 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, POINTST_OP, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 176:
#line 1774 "gram1.y"
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
#line 1789 "gram1.y"
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
#line 1805 "gram1.y"
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
#line 1823 "gram1.y"
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
#line 1843 "gram1.y"
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
#line 1863 "gram1.y"
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
#line 1885 "gram1.y"
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
#line 1902 "gram1.y"
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
#line 1920 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 185:
#line 1927 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 186:
#line 1934 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(q, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 187:
#line 1941 "gram1.y"
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
#line 1954 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,NAMELIST_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 189:
#line 1961 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(r, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 190:
#line 1968 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(q, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 191:
#line 1979 "gram1.y"
    { (yyval.symbol) =  make_local_entity((yyvsp[(2) - (3)].hash_entry), NAMELIST_NAME,global_default,LOCAL); ;}
    break;

  case 192:
#line 1983 "gram1.y"
    { (yyval.symbol) = NULL; /*make_common(look_up_sym("*"));*/ ;}
    break;

  case 193:
#line 1985 "gram1.y"
    { (yyval.symbol) = make_common((yyvsp[(2) - (3)].hash_entry)); ;}
    break;

  case 194:
#line 1990 "gram1.y"
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
#line 2008 "gram1.y"
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
#line 2019 "gram1.y"
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
#line 2031 "gram1.y"
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
#line 2043 "gram1.y"
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
#line 2057 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,EQUI_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node),
			     LLNULL, LLNULL);
	    ;}
    break;

  case 200:
#line 2063 "gram1.y"
    { 
	      add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 201:
#line 2070 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EQUI_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
           ;}
    break;

  case 202:
#line 2076 "gram1.y"
    { PTR_LLND p;
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (3)].ll_node), p, SMNULL);
	    ;}
    break;

  case 203:
#line 2082 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 204:
#line 2090 "gram1.y"
    {  PTR_SYMB s;
           s=make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
           (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$=$1; $$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 205:
#line 2097 "gram1.y"
    {  PTR_SYMB s;
           s=make_array((yyvsp[(1) - (4)].hash_entry),TYNULL,LLNULL,0,LOCAL);
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 207:
#line 2116 "gram1.y"
    { PTR_LLND p;
              data_stat = NO;
	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL,
			    SMNULL);
              p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,DATA_DECL, SMNULL, p, LLNULL, LLNULL);
            ;}
    break;

  case 210:
#line 2130 "gram1.y"
    {data_stat = YES;;}
    break;

  case 211:
#line 2134 "gram1.y"
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
#line 2179 "gram1.y"
    {;;}
    break;

  case 223:
#line 2183 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);;}
    break;

  case 224:
#line 2187 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL); 
              (yyval.symbol)->attr = (yyval.symbol)->attr | DATA_BIT; 
            ;}
    break;

  case 225:
#line 2193 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_SUBS, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 226:
#line 2197 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_RANGE, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 227:
#line 2201 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 228:
#line 2203 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 229:
#line 2207 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 230:
#line 2209 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 231:
#line 2213 "gram1.y"
    {(yyval.ll_node)= make_llnd(fi, DATA_IMPL_DO, (yyvsp[(2) - (7)].ll_node), (yyvsp[(6) - (7)].ll_node), (yyvsp[(4) - (7)].symbol)); ;}
    break;

  case 232:
#line 2217 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 233:
#line 2219 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 234:
#line 2223 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 235:
#line 2225 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 236:
#line 2227 "gram1.y"
    {
              (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr2 = (yyvsp[(3) - (3)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); 
            ;}
    break;

  case 237:
#line 2232 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 251:
#line 2256 "gram1.y"
    {if((yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->variant != TYPE_NAME)
               errstr("Undefined type %s",(yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->ident,319); 
           ;}
    break;

  case 268:
#line 2301 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ICON_EXPR, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 269:
#line 2303 "gram1.y"
    {
              PTR_LLND p;

              p = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 270:
#line 2310 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 271:
#line 2317 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 272:
#line 2324 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 273:
#line 2333 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 274:
#line 2335 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 275:
#line 2337 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 276:
#line 2341 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 277:
#line 2343 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 278:
#line 2347 "gram1.y"
    {
              PTR_LLND p;

              p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
              p->entry.ival = atoi(yytext);
              p->type = global_int;
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 279:
#line 2356 "gram1.y"
    {
              PTR_LLND p;
 
              p = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 280:
#line 2363 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 281:
#line 2370 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 282:
#line 2372 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 283:
#line 2376 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
             (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
           ;}
    break;

  case 284:
#line 2380 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol)); 
            (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
          ;}
    break;

  case 285:
#line 2386 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 286:
#line 2388 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), EXPR_LIST); ;}
    break;

  case 287:
#line 2392 "gram1.y"
    { as_op_kwd_ = YES; ;}
    break;

  case 288:
#line 2396 "gram1.y"
    { as_op_kwd_ = NO; ;}
    break;

  case 289:
#line 2401 "gram1.y"
    { 
             PTR_SYMB s; 
             s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
	     (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 290:
#line 2408 "gram1.y"
    { PTR_SYMB s;
	      s = make_function((yyvsp[(3) - (4)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,OPERATOR_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 291:
#line 2415 "gram1.y"
    { PTR_SYMB s;
	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,ASSIGNMENT_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 292:
#line 2425 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 293:
#line 2427 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 294:
#line 2431 "gram1.y"
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
#line 2443 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, MODULE_PROC_STMT, SMNULL, (yyvsp[(2) - (2)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 296:
#line 2446 "gram1.y"
    { PTR_SYMB s;
 	      PTR_LLND q;

	      s = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	    ;}
    break;

  case 297:
#line 2455 "gram1.y"
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
#line 2468 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
              /*add_scope_level($3->entry.Template.func_hedr, YES);*/ /*17.06.01*/
              copy_module_scope((yyvsp[(3) - (3)].symbol),LLNULL); /*17.03.03*/
              colon_flag = NO;
            ;}
    break;

  case 299:
#line 2474 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), (yyvsp[(6) - (6)].ll_node), LLNULL, LLNULL); 
              /*add_scope_level(module_scope, YES); *//* 17.06.01*/
              copy_module_scope((yyvsp[(3) - (6)].symbol),(yyvsp[(6) - (6)].ll_node)); /*17.03.03 */
              colon_flag = NO;
            ;}
    break;

  case 300:
#line 2480 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, LLNULL, LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 301:
#line 2486 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, (yyvsp[(7) - (7)].ll_node), LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (7)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 302:
#line 2494 "gram1.y"
    {
              if ((yyvsp[(1) - (1)].hash_entry)->id_attr == SMNULL)
	         warn1("Unknown module %s", (yyvsp[(1) - (1)].hash_entry)->ident,308);
              (yyval.symbol) = make_global_entity((yyvsp[(1) - (1)].hash_entry), MODULE_NAME, global_default, NO);
	      module_scope = (yyval.symbol)->entry.Template.func_hedr;
           
            ;}
    break;

  case 303:
#line 2504 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 304:
#line 2506 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 305:
#line 2510 "gram1.y"
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
#line 2531 "gram1.y"
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
#line 2556 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 308:
#line 2558 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 309:
#line 2562 "gram1.y"
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
#line 2593 "gram1.y"
    { ndim = 0;	explicit_shape = 1; (yyval.ll_node) = LLNULL; ;}
    break;

  case 311:
#line 2595 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 312:
#line 2598 "gram1.y"
    { ndim = 0; explicit_shape = 1;;}
    break;

  case 313:
#line 2599 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
	    ;}
    break;

  case 314:
#line 2604 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 315:
#line 2608 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
	      ++ndim;
	    ;}
    break;

  case 316:
#line 2616 "gram1.y"
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
#line 2625 "gram1.y"
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
#line 2634 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      ++ndim;
	    ;}
    break;

  case 319:
#line 2644 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,STAR_RANGE, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
              explicit_shape = 0;
	    ;}
    break;

  case 321:
#line 2653 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 322:
#line 2655 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 323:
#line 2659 "gram1.y"
    {PTR_LABEL p;
	     p = make_label_node(fi,convci(yyleng, yytext));
	     p->scope = cur_scope();
	     (yyval.ll_node) = make_llnd_label(fi,LABEL_REF, p);
	  ;}
    break;

  case 324:
#line 2667 "gram1.y"
    { /*PTR_LLND l;*/

          /*   l = make_llnd(fi, EXPR_LIST, $3, LLNULL, SMNULL);*/
             (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
             redefine_func_arg_type();
           ;}
    break;

  case 325:
#line 2682 "gram1.y"
    { /*undeftype = YES;
	    setimpl(TYNULL, (int)'a', (int)'z'); FB COMMENTED---> NOT QUITE RIGHT BUT AVOID PB WITH COMMON*/
	    (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	  ;}
    break;

  case 326:
#line 2689 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 327:
#line 2691 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 328:
#line 2695 "gram1.y"
    { 

            (yyval.ll_node) = make_llnd(fi, IMPL_TYPE, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
            (yyval.ll_node)->type = vartype;
          ;}
    break;

  case 329:
#line 2710 "gram1.y"
    { implkwd = YES; ;}
    break;

  case 330:
#line 2711 "gram1.y"
    { vartype = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 331:
#line 2715 "gram1.y"
    { (yyval.data_type) = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 332:
#line 2717 "gram1.y"
    { (yyval.data_type) = (yyvsp[(1) - (1)].data_type);;}
    break;

  case 333:
#line 2729 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 334:
#line 2731 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 335:
#line 2735 "gram1.y"
    {
	      setimpl(vartype, (int)(yyvsp[(1) - (1)].charv), (int)(yyvsp[(1) - (1)].charv));
	      (yyval.ll_node) = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.cval = (yyvsp[(1) - (1)].charv);
	    ;}
    break;

  case 336:
#line 2741 "gram1.y"
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
#line 2753 "gram1.y"
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
#line 2764 "gram1.y"
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
#line 2781 "gram1.y"
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
#line 2819 "gram1.y"
    { (yyval.ll_node) = LLNULL; endioctl(); ;}
    break;

  case 343:
#line 2821 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);  endioctl();;}
    break;

  case 344:
#line 2825 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 345:
#line 2827 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 346:
#line 2829 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
	      l->type = (yyvsp[(2) - (2)].ll_node)->type;
              (yyval.ll_node) = l; 
	    ;}
    break;

  case 347:
#line 2840 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 348:
#line 2844 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 349:
#line 2850 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 350:
#line 2852 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 351:
#line 2856 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 352:
#line 2858 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 353:
#line 2860 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 354:
#line 2864 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 355:
#line 2866 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 356:
#line 2870 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 357:
#line 2872 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 358:
#line 2874 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 359:
#line 2876 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 360:
#line 2878 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 361:
#line 2880 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 362:
#line 2882 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(1) - (2)].hash_entry), (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 363:
#line 2884 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 364:
#line 2886 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 365:
#line 2888 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eq.", EQ_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 366:
#line 2890 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".gt.", GT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 367:
#line 2892 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".lt.", LT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 368:
#line 2894 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", GTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 369:
#line 2896 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", LTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 370:
#line 2898 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ne.", NOTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 371:
#line 2900 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eqv.", EQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 372:
#line 2902 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".neqv.", NEQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 373:
#line 2904 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".xor.", XOR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 374:
#line 2906 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".or.", OR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 375:
#line 2908 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".and.", AND_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 376:
#line 2910 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".not.", NOT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 377:
#line 2912 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("//", CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 378:
#line 2914 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(2) - (3)].hash_entry), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 379:
#line 2917 "gram1.y"
    { (yyval.token) = ADD_OP; ;}
    break;

  case 380:
#line 2918 "gram1.y"
    { (yyval.token) = SUBT_OP; ;}
    break;

  case 381:
#line 2930 "gram1.y"
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
#line 3004 "gram1.y"
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
#line 3016 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 384:
#line 3018 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 385:
#line 3022 "gram1.y"
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
#line 3153 "gram1.y"
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
#line 3203 "gram1.y"
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
#line 3247 "gram1.y"
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
#line 3289 "gram1.y"
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
#line 3347 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 391:
#line 3349 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 392:
#line 3351 "gram1.y"
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
#line 3391 "gram1.y"
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
#line 3433 "gram1.y"
    { 
	      if ((yyvsp[(1) - (2)].ll_node)->type->variant == T_STRING) {
                 (yyvsp[(1) - (2)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (2)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node); (yyval.ll_node)->type = global_string;
              }
              else errstr("can't subscript of %s", (yyvsp[(1) - (2)].ll_node)->entry.Template.symbol->ident,44);
            ;}
    break;

  case 395:
#line 3443 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 396:
#line 3445 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 397:
#line 3449 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 398:
#line 3453 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 399:
#line 3455 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 400:
#line 3459 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 401:
#line 3461 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 402:
#line 3467 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 403:
#line 3469 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 404:
#line 3475 "gram1.y"
    {
              if ((yyvsp[(2) - (2)].ll_node) != LLNULL)
		 (yyval.ll_node) = make_llnd(fi, ARRAY_OP, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); 
	      else 
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);
             ;}
    break;

  case 405:
#line 3485 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 1;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 406:
#line 3491 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 0;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 407:
#line 3498 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,FLOAT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_float;
	    ;}
    break;

  case 408:
#line 3504 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DOUBLE_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_double;
	    ;}
    break;

  case 409:
#line 3512 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.ival = atoi(yytext);
	      (yyval.ll_node)->type = global_int;
	    ;}
    break;

  case 410:
#line 3520 "gram1.y"
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
#line 3536 "gram1.y"
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
#line 3546 "gram1.y"
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
#line 3559 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,COMPLEX_VAL, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL);
	      (yyval.ll_node)->type = global_complex;
	    ;}
    break;

  case 414:
#line 3566 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 415:
#line 3568 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 416:
#line 3591 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 417:
#line 3593 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 418:
#line 3595 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),SMNULL),(yyvsp[(5) - (5)].ll_node),SMNULL); ;}
    break;

  case 419:
#line 3597 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (4)].ll_node),LLNULL,SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 420:
#line 3599 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (4)].ll_node),SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 421:
#line 3601 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 422:
#line 3603 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (2)].ll_node),SMNULL); ;}
    break;

  case 423:
#line 3605 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL); ;}
    break;

  case 424:
#line 3608 "gram1.y"
    {in_vec=YES;;}
    break;

  case 425:
#line 3608 "gram1.y"
    {in_vec=NO;;}
    break;

  case 426:
#line 3609 "gram1.y"
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
#line 3623 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 428:
#line 3625 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 429:
#line 3648 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 430:
#line 3650 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 431:
#line 3652 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                  endioctl();
                ;}
    break;

  case 432:
#line 3668 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 433:
#line 3670 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 434:
#line 3672 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
             endioctl();
           ;}
    break;

  case 435:
#line 3685 "gram1.y"
    {stat_alloc = LLNULL;;}
    break;

  case 436:
#line 3689 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 437:
#line 3691 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 438:
#line 3699 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 439:
#line 3701 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 440:
#line 3703 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 441:
#line 3705 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 442:
#line 3759 "gram1.y"
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
#line 3781 "gram1.y"
    {
              make_extend((yyvsp[(3) - (3)].symbol));
              (yyval.bf_node) = BFNULL; 
              /* delete_beyond_scope_level(pred_bfnd); */
             ;}
    break;

  case 444:
#line 3794 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	    bind(); 
	    delete_beyond_scope_level(pred_bfnd);
	    position = IN_OUTSIDE;
          ;}
    break;

  case 445:
#line 3803 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 446:
#line 3806 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 447:
#line 3856 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = LOGIF_NODE;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 448:
#line 3862 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 449:
#line 3867 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (3)].ll_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 450:
#line 3885 "gram1.y"
    { make_elseif((yyvsp[(4) - (7)].ll_node),(yyvsp[(7) - (7)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL;;}
    break;

  case 451:
#line 3887 "gram1.y"
    { make_else((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 452:
#line 3889 "gram1.y"
    { make_endif((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 453:
#line 3891 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 454:
#line 3893 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CONTAINS_STMT, SMNULL, LLNULL, LLNULL, LLNULL); ;}
    break;

  case 455:
#line 3896 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = FORALL_STAT;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 456:
#line 3902 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 457:
#line 3904 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node); (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 458:
#line 3906 "gram1.y"
    { make_endforall((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 459:
#line 3909 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 460:
#line 3911 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 461:
#line 3913 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 462:
#line 3940 "gram1.y"
    { 	     
	     /*  if($5 && $5->labdefined)
		 execerr("no backward DO loops", (char *)NULL); */
	       (yyval.bf_node) = make_do(WHILE_NODE, LBNULL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL);
	       /*$$->entry.Template.ll_ptr3 = $1;*/	     
           ;}
    break;

  case 463:
#line 3949 "gram1.y"
    {
               if( (yyvsp[(4) - (7)].label) && (yyvsp[(4) - (7)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(WHILE_NODE, (yyvsp[(4) - (7)].label), SMNULL, (yyvsp[(7) - (7)].ll_node), LLNULL, LLNULL);            
	    ;}
    break;

  case 464:
#line 3957 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 465:
#line 3959 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(5) - (6)].ll_node);;}
    break;

  case 466:
#line 3961 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 467:
#line 3966 "gram1.y"
    {  
               if( (yyvsp[(4) - (11)].label) && (yyvsp[(4) - (11)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (11)].label), (yyvsp[(7) - (11)].symbol), (yyvsp[(9) - (11)].ll_node), (yyvsp[(11) - (11)].ll_node), LLNULL);            
	    ;}
    break;

  case 468:
#line 3973 "gram1.y"
    {
               if( (yyvsp[(4) - (13)].label) && (yyvsp[(4) - (13)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (13)].label), (yyvsp[(7) - (13)].symbol), (yyvsp[(9) - (13)].ll_node), (yyvsp[(11) - (13)].ll_node), (yyvsp[(13) - (13)].ll_node));            
	    ;}
    break;

  case 469:
#line 3981 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CASE_NODE, (yyvsp[(4) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 470:
#line 3983 "gram1.y"
    { /*PTR_LLND p;*/
	     /* p = make_llnd(fi, DEFAULT, LLNULL, LLNULL, SMNULL); */
	      (yyval.bf_node) = get_bfnd(fi, DEFAULT_NODE, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 471:
#line 3987 "gram1.y"
    { make_endselect((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 472:
#line 3990 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(6) - (7)].ll_node), LLNULL, LLNULL) ; ;}
    break;

  case 473:
#line 3992 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(7) - (8)].ll_node), LLNULL, (yyvsp[(1) - (8)].ll_node)) ; ;}
    break;

  case 474:
#line 3996 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 475:
#line 4002 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 476:
#line 4004 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 477:
#line 4006 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 478:
#line 4008 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL); ;}
    break;

  case 479:
#line 4012 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 480:
#line 4014 "gram1.y"
    { PTR_LLND p;
	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 481:
#line 4022 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 482:
#line 4024 "gram1.y"
    { (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSTRUCT_NAME, global_default,
                                     LOCAL); ;}
    break;

  case 483:
#line 4030 "gram1.y"
    {(yyval.hash_entry) = HSNULL;;}
    break;

  case 484:
#line 4032 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry);;}
    break;

  case 485:
#line 4036 "gram1.y"
    {(yyval.hash_entry) = look_up_sym(yytext);;}
    break;

  case 486:
#line 4040 "gram1.y"
    { PTR_SYMB s;
	             s = make_local_entity( (yyvsp[(1) - (2)].hash_entry), CONSTRUCT_NAME, global_default, LOCAL);             
                    (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
                   ;}
    break;

  case 487:
#line 4061 "gram1.y"
    { (yyval.bf_node) = make_if((yyvsp[(4) - (5)].ll_node)); ;}
    break;

  case 488:
#line 4064 "gram1.y"
    { (yyval.bf_node) = make_forall((yyvsp[(4) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node)); ;}
    break;

  case 489:
#line 4068 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 490:
#line 4070 "gram1.y"
    { PTR_LLND p;	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 491:
#line 4077 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, FORALL_OP, (yyvsp[(3) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); ;}
    break;

  case 492:
#line 4081 "gram1.y"
    { (yyval.ll_node)=LLNULL;;}
    break;

  case 493:
#line 4083 "gram1.y"
    { (yyval.ll_node)=(yyvsp[(2) - (2)].ll_node);;}
    break;

  case 494:
#line 4099 "gram1.y"
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
#line 4112 "gram1.y"
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
#line 4135 "gram1.y"
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
#line 4158 "gram1.y"
    { (yyval.label) = LBNULL; ;}
    break;

  case 498:
#line 4160 "gram1.y"
    {
	       (yyval.label)  = make_label_node(fi,convci(yyleng, yytext));
	       (yyval.label)->scope = cur_scope();
	    ;}
    break;

  case 499:
#line 4167 "gram1.y"
    { make_endwhere((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 500:
#line 4169 "gram1.y"
    { make_elsewhere((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 501:
#line 4171 "gram1.y"
    { make_elsewhere_mask((yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 502:
#line 4173 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 503:
#line 4175 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), LLNULL, (yyvsp[(1) - (6)].ll_node)); ;}
    break;

  case 504:
#line 4180 "gram1.y"
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
#line 4255 "gram1.y"
    { /*PTR_SYMB s;*/
	
	      /*s = make_scalar($2, TYNULL, LOCAL);*/
  	      (yyval.bf_node) = get_bfnd(fi, POINTER_ASSIGN_STAT, SMNULL, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), LLNULL);
	    ;}
    break;

  case 506:
#line 4267 "gram1.y"
    { PTR_SYMB p;

	      p = make_scalar((yyvsp[(5) - (5)].hash_entry), TYNULL, LOCAL);
	      p->variant = LABEL_VAR;
  	      (yyval.bf_node) = get_bfnd(fi,ASSLAB_STAT, p, (yyvsp[(3) - (5)].ll_node),LLNULL,LLNULL);
            ;}
    break;

  case 507:
#line 4274 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONT_STAT,SMNULL,LLNULL,LLNULL,LLNULL); ;}
    break;

  case 509:
#line 4277 "gram1.y"
    { inioctl = NO; ;}
    break;

  case 510:
#line 4279 "gram1.y"
    { PTR_LLND	p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(10) - (10)].ll_node), LLNULL, SMNULL);
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(8) - (10)].ll_node), p, SMNULL);
	      (yyval.bf_node)= get_bfnd(fi,ARITHIF_NODE, SMNULL, (yyvsp[(4) - (10)].ll_node),
			    make_llnd(fi,EXPR_LIST, (yyvsp[(6) - (10)].ll_node), p, SMNULL), LLNULL);
	      thiswasbranch = YES;
            ;}
    break;

  case 511:
#line 4288 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (1)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT, $1, LLNULL, LLNULL, LLNULL);
*/	      endioctl(); 
            ;}
    break;

  case 512:
#line 4295 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (3)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT,$1,LLNULL,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 513:
#line 4302 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, PLAIN);
/*	      match_parameters($1, $3);
	      $$= get_bfnd(fi,PROC_STAT,$1,$3,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 514:
#line 4310 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,RETURN_STAT,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = YES;
	    ;}
    break;

  case 515:
#line 4315 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,(yyvsp[(1) - (3)].token),SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = ((yyvsp[(1) - (3)].token) == STOP_STAT);
	    ;}
    break;

  case 516:
#line 4320 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CYCLE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 517:
#line 4323 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, EXIT_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 518:
#line 4326 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, ALLOCATE_STMT,  SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc, LLNULL); ;}
    break;

  case 519:
#line 4329 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, DEALLOCATE_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc , LLNULL); ;}
    break;

  case 520:
#line 4332 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, NULLIFY_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 521:
#line 4335 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_NODE, SMNULL, (yyvsp[(4) - (8)].ll_node), (yyvsp[(6) - (8)].ll_node), (yyvsp[(8) - (8)].ll_node)); ;}
    break;

  case 522:
#line 4353 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 523:
#line 4357 "gram1.y"
    {
	      (yyval.bf_node)=get_bfnd(fi,GOTO_NODE,SMNULL,LLNULL,LLNULL,(PTR_LLND)(yyvsp[(3) - (3)].ll_node));
	      thiswasbranch = YES;
	    ;}
    break;

  case 524:
#line 4362 "gram1.y"
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
#line 4381 "gram1.y"
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
#line 4400 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,COMGOTO_NODE, SMNULL, (yyvsp[(4) - (7)].ll_node), (yyvsp[(7) - (7)].ll_node), LLNULL); ;}
    break;

  case 529:
#line 4408 "gram1.y"
    { (yyval.symbol) = make_procedure((yyvsp[(3) - (4)].hash_entry), YES); ;}
    break;

  case 530:
#line 4412 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 531:
#line 4417 "gram1.y"
    { 
               (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
               endioctl();
            ;}
    break;

  case 532:
#line 4424 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 533:
#line 4426 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 534:
#line 4428 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,LABEL_ARG,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 535:
#line 4431 "gram1.y"
    { (yyval.token) = PAUSE_NODE; ;}
    break;

  case 536:
#line 4432 "gram1.y"
    { (yyval.token) = STOP_STAT; ;}
    break;

  case 537:
#line 4443 "gram1.y"
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
#line 4458 "gram1.y"
    { intonly = YES; ;}
    break;

  case 539:
#line 4462 "gram1.y"
    { intonly = NO; ;}
    break;

  case 540:
#line 4470 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 541:
#line 4473 "gram1.y"
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
#line 4483 "gram1.y"
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
#line 4496 "gram1.y"
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
#line 4509 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 545:
#line 4513 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 546:
#line 4516 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 547:
#line 4519 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 548:
#line 4523 "gram1.y"
    { (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (4)].ll_node);
		  (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (4)].bf_node); ;}
    break;

  case 549:
#line 4532 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 550:
#line 4535 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 551:
#line 4539 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 552:
#line 4541 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 553:
#line 4547 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 554:
#line 4551 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, BACKSPACE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 555:
#line 4553 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, REWIND_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 556:
#line 4555 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, ENDFILE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 557:
#line 4562 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 558:
#line 4566 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 559:
#line 4568 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, OPEN_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 560:
#line 4570 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, CLOSE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 561:
#line 4574 "gram1.y"
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
#line 4593 "gram1.y"
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
#line 4609 "gram1.y"
    { PTR_LLND p;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"unit";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, p, (yyvsp[(2) - (3)].ll_node), SMNULL);
		  endioctl();
		;}
    break;

  case 564:
#line 4620 "gram1.y"
    { 
		  (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);
		  endioctl();
		 ;}
    break;

  case 565:
#line 4627 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); endioctl();;}
    break;

  case 566:
#line 4629 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl();;}
    break;

  case 567:
#line 4633 "gram1.y"
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
#line 4659 "gram1.y"
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
#line 4674 "gram1.y"
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
#line 4689 "gram1.y"
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
#line 4706 "gram1.y"
    { PTR_LLND p;
                  
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 572:
#line 4714 "gram1.y"
    { PTR_LLND p;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 573:
#line 4723 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  (yyval.ll_node)->entry.string_val = copys(yytext);
		  (yyval.ll_node)->type = global_string;
	        ;}
    break;

  case 574:
#line 4731 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, READ_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 575:
#line 4736 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, WRITE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 576:
#line 4741 "gram1.y"
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
#line 4763 "gram1.y"
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
#line 4779 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);;}
    break;

  case 579:
#line 4781 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST);;}
    break;

  case 580:
#line 4785 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 581:
#line 4787 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
		;}
    break;

  case 582:
#line 4794 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);  (yyval.ll_node)->type = (yyvsp[(1) - (1)].ll_node)->type;;}
    break;

  case 583:
#line 4796 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 584:
#line 4798 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 585:
#line 4802 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 586:
#line 4804 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 587:
#line 4806 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 588:
#line 4808 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 589:
#line 4810 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 590:
#line 4812 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 591:
#line 4816 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);
	          (yyval.ll_node)->type = global_complex; ;}
    break;

  case 592:
#line 4819 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (3)].ll_node)->type; ;}
    break;

  case 593:
#line 4822 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 594:
#line 4828 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 595:
#line 4834 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 596:
#line 4842 "gram1.y"
    { inioctl = YES; ;}
    break;

  case 597:
#line 4846 "gram1.y"
    { startioctl();;}
    break;

  case 598:
#line 4854 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 599:
#line 4856 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 600:
#line 4860 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 601:
#line 4862 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 602:
#line 4864 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,(yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 603:
#line 4869 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 604:
#line 4874 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 605:
#line 4879 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 606:
#line 4884 "gram1.y"
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
#line 4893 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 608:
#line 4898 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 609:
#line 4903 "gram1.y"
    { comments = cur_comment = CMNULL; ;}
    break;

  case 610:
#line 4905 "gram1.y"
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

  case 672:
#line 4986 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 673:
#line 4988 "gram1.y"
    { PTR_SYMB s;
                if((yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2)
                {
                  s = (yyvsp[(3) - (3)].ll_node)->entry.Template.ll_ptr1->entry.Template.symbol;
                  s->attr = s->attr | COMMON_BIT;
                }
	        add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	      ;}
    break;

  case 674:
#line 4999 "gram1.y"
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

  case 675:
#line 5019 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DYNAMIC_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 676:
#line 5023 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 677:
#line 5025 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 678:
#line 5029 "gram1.y"
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

  case 679:
#line 5042 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INHERIT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
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
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
              else
                s->attr = s->attr | INHERIT_BIT;        
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 683:
#line 5063 "gram1.y"
    { PTR_LLND q;
             q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              /* (void)fprintf(stderr,"hpf.gram: shadow\n");*/ 
	     (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_DIR,SMNULL,q,(yyvsp[(4) - (4)].ll_node),LLNULL);
            ;}
    break;

  case 684:
#line 5074 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 685:
#line 5078 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 686:
#line 5080 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 687:
#line 5084 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 688:
#line 5086 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 689:
#line 5088 "gram1.y"
    {
            if(parstate!=INEXEC) 
               err("Illegal shadow width specification", 56);  
            (yyval.ll_node) = make_llnd(fi,SHADOW_NAMES_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
          ;}
    break;

  case 690:
#line 5103 "gram1.y"
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

  case 691:
#line 5115 "gram1.y"
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
#line 5135 "gram1.y"
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
#line 5155 "gram1.y"
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

  case 694:
#line 5177 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 695:
#line 5183 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 696:
#line 5192 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 697:
#line 5200 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 698:
#line 5206 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 699:
#line 5214 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 700:
#line 5221 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 701:
#line 5227 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 702:
#line 5236 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 703:
#line 5240 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 704:
#line 5246 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 705:
#line 5254 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 706:
#line 5268 "gram1.y"
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

  case 707:
#line 5281 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 708:
#line 5287 "gram1.y"
    { PTR_LLND q;
             if(!(yyvsp[(4) - (5)].ll_node))
               err("Distribution format list is omitted", 51);
            /* if($6)
               err("NEW_VALUE specification in DISTRIBUTE directive");*/
             q = set_ll_list((yyvsp[(3) - (5)].ll_node),LLNULL,EXPR_LIST);
	     (yyval.bf_node) = get_bfnd(fi,DVM_DISTRIBUTE_DIR,SMNULL,q,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node));
            ;}
    break;

  case 709:
#line 5303 "gram1.y"
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

  case 710:
#line 5318 "gram1.y"
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

  case 711:
#line 5346 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 712:
#line 5348 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 713:
#line 5352 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 714:
#line 5354 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 715:
#line 5358 "gram1.y"
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

  case 716:
#line 5387 "gram1.y"
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

  case 717:
#line 5410 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 718:
#line 5430 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 719:
#line 5432 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 720:
#line 5436 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 721:
#line 5457 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 722:
#line 5459 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 723:
#line 5462 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 724:
#line 5471 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 725:
#line 5475 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 726:
#line 5480 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 727:
#line 5482 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 728:
#line 5484 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 729:
#line 5486 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 730:
#line 5492 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 731:
#line 5494 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 732:
#line 5498 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 733:
#line 5508 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
    break;

  case 734:
#line 5512 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 735:
#line 5514 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 736:
#line 5519 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 737:
#line 5521 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 738:
#line 5525 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 739:
#line 5529 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 740:
#line 5535 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 741:
#line 5545 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 742:
#line 5547 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 743:
#line 5551 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 744:
#line 5553 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 745:
#line 5555 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 746:
#line 5562 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 747:
#line 5579 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 748:
#line 5581 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 749:
#line 5585 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 750:
#line 5587 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 751:
#line 5591 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 752:
#line 5598 "gram1.y"
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

  case 753:
#line 5608 "gram1.y"
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

  case 754:
#line 5637 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 755:
#line 5652 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 756:
#line 5659 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 757:
#line 5677 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 758:
#line 5679 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 759:
#line 5683 "gram1.y"
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

  case 760:
#line 5697 "gram1.y"
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

  case 761:
#line 5723 "gram1.y"
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

  case 762:
#line 5736 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 763:
#line 5752 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 764:
#line 5754 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 765:
#line 5757 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 766:
#line 5759 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 767:
#line 5765 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 768:
#line 5769 "gram1.y"
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

  case 769:
#line 5797 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 770:
#line 5799 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 771:
#line 5803 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 772:
#line 5811 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 773:
#line 5817 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 774:
#line 5820 "gram1.y"
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

  case 775:
#line 5877 "gram1.y"
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

  case 776:
#line 5941 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 777:
#line 5943 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 778:
#line 5946 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 779:
#line 5950 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
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
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 782:
#line 5975 "gram1.y"
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

  case 783:
#line 5987 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 784:
#line 5991 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 785:
#line 5995 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 786:
#line 6005 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 787:
#line 6010 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 788:
#line 6015 "gram1.y"
    {
                 type_opt = COMMON_BIT;
                 (yyval.ll_node) = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                ;}
    break;

  case 789:
#line 6022 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 790:
#line 6030 "gram1.y"
    {ndim = 0;;}
    break;

  case 791:
#line 6031 "gram1.y"
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

  case 792:
#line 6042 "gram1.y"
    { PTR_LLND  q;
             if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		q = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL);
	      ++ndim;
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), q, EXPR_LIST);
            ;}
    break;

  case 793:
#line 6053 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 794:
#line 6055 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 795:
#line 6059 "gram1.y"
    {PTR_SYMB s;
           /* s = make_scalar($1,TYNULL,LOCAL);*/
            s = make_array((yyvsp[(1) - (1)].hash_entry),TYNULL,LLNULL,0,LOCAL);
            s->attr = s->attr | DVM_POINTER_BIT;
            if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT))
               errstr( "Inconsistent declaration of identifier %s", s->ident, 16);     
            (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL,s);
            ;}
    break;

  case 796:
#line 6070 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 797:
#line 6074 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 798:
#line 6076 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 799:
#line 6080 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 800:
#line 6091 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 801:
#line 6095 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 802:
#line 6097 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 803:
#line 6101 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 804:
#line 6113 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 805:
#line 6115 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 806:
#line 6122 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 807:
#line 6124 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 808:
#line 6128 "gram1.y"
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

  case 809:
#line 6144 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 810:
#line 6154 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                 ;}
    break;

  case 811:
#line 6163 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 812:
#line 6165 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 814:
#line 6172 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 815:
#line 6175 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 816:
#line 6180 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
           errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
         ;}
    break;

  case 817:
#line 6190 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 818:
#line 6192 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 819:
#line 6196 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 820:
#line 6198 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 821:
#line 6206 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 822:
#line 6208 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 823:
#line 6212 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 824:
#line 6214 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 835:
#line 6231 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 836:
#line 6236 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 837:
#line 6240 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 838:
#line 6244 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 839:
#line 6248 "gram1.y"
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

  case 840:
#line 6261 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 841:
#line 6265 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 842:
#line 6269 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 843:
#line 6273 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 844:
#line 6276 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 845:
#line 6278 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 846:
#line 6280 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 847:
#line 6284 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 848:
#line 6286 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 849:
#line 6290 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 850:
#line 6295 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 851:
#line 6299 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 852:
#line 6303 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 853:
#line 6305 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 854:
#line 6309 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 855:
#line 6317 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 856:
#line 6323 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 857:
#line 6329 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 858:
#line 6333 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 859:
#line 6335 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 860:
#line 6339 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 861:
#line 6341 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 862:
#line 6345 "gram1.y"
    { /*  PTR_LLND p;
                       p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
                       p->entry.string_val = (char *) "corner";
                       p->type = global_string;
                   */
                   (yyvsp[(1) - (7)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (7)].ll_node);  
                   (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 863:
#line 6357 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 864:
#line 6359 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 865:
#line 6363 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 866:
#line 6367 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 867:
#line 6369 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 868:
#line 6373 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 869:
#line 6375 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 870:
#line 6377 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 871:
#line 6379 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 872:
#line 6381 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 873:
#line 6383 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 874:
#line 6385 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 875:
#line 6389 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
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
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 879:
#line 6405 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 880:
#line 6412 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 881:
#line 6418 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 882:
#line 6422 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 883:
#line 6425 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 884:
#line 6429 "gram1.y"
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

  case 885:
#line 6442 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 886:
#line 6444 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 887:
#line 6448 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 888:
#line 6450 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 889:
#line 6455 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 890:
#line 6461 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 891:
#line 6467 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 892:
#line 6473 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 893:
#line 6479 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 894:
#line 6485 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 895:
#line 6491 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 896:
#line 6497 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 897:
#line 6503 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 898:
#line 6512 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 899:
#line 6518 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 900:
#line 6535 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 901:
#line 6543 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 902:
#line 6551 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 903:
#line 6553 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 904:
#line 6555 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 905:
#line 6559 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 906:
#line 6563 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 907:
#line 6565 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 908:
#line 6569 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 909:
#line 6571 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 910:
#line 6579 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 911:
#line 6583 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 912:
#line 6594 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 913:
#line 6598 "gram1.y"
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

  case 914:
#line 6616 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 915:
#line 6618 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 916:
#line 6622 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 917:
#line 6624 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 918:
#line 6628 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 919:
#line 6630 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 920:
#line 6634 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 921:
#line 6638 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 922:
#line 6642 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 923:
#line 6651 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 924:
#line 6655 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 925:
#line 6659 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 926:
#line 6664 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 927:
#line 6668 "gram1.y"
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

  case 928:
#line 6680 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 929:
#line 6682 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 930:
#line 6686 "gram1.y"
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 931:
#line 6691 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 932:
#line 6695 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 933:
#line 6697 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 934:
#line 6701 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 935:
#line 6703 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 936:
#line 6707 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 937:
#line 6712 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 938:
#line 6719 "gram1.y"
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

  case 939:
#line 6742 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 940:
#line 6744 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 941:
#line 6746 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 942:
#line 6748 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 943:
#line 6750 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 944:
#line 6754 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 945:
#line 6765 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 946:
#line 6769 "gram1.y"
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

  case 947:
#line 6784 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 948:
#line 6791 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 949:
#line 6797 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 950:
#line 6799 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 951:
#line 6803 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 952:
#line 6807 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 953:
#line 6815 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 954:
#line 6819 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 955:
#line 6823 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 956:
#line 6831 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 957:
#line 6836 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 958:
#line 6850 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 959:
#line 6852 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 960:
#line 6856 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 961:
#line 6858 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 962:
#line 6867 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 963:
#line 6869 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 964:
#line 6871 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 965:
#line 6873 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 966:
#line 6909 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 967:
#line 6913 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 968:
#line 6917 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 969:
#line 6921 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 970:
#line 6925 "gram1.y"
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

  case 971:
#line 6937 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 972:
#line 6939 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 973:
#line 6943 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 974:
#line 6946 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 975:
#line 6948 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 976:
#line 6952 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 977:
#line 6957 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 978:
#line 6964 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 979:
#line 6967 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 980:
#line 6975 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 981:
#line 6979 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 982:
#line 6983 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 983:
#line 6986 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 984:
#line 6994 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_EXIT_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 985:
#line 6998 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 986:
#line 7002 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 987:
#line 7006 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 988:
#line 7010 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 989:
#line 7014 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 990:
#line 7018 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 991:
#line 7021 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 992:
#line 7023 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 993:
#line 7027 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 994:
#line 7029 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 995:
#line 7031 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 996:
#line 7035 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 997:
#line 7039 "gram1.y"
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

  case 998:
#line 7051 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 999:
#line 7053 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1000:
#line 7057 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1001:
#line 7059 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1002:
#line 7063 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1003:
#line 7065 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 1004:
#line 7069 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 1005:
#line 7073 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 1006:
#line 7079 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 1007:
#line 7091 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1008:
#line 7093 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1009:
#line 7097 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1010:
#line 7099 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1011:
#line 7103 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1012:
#line 7111 "gram1.y"
    { 
                PTR_LLND q;
                if((yyvsp[(16) - (16)].ll_node))
                  q = make_llnd(fi,ARRAY_OP, (yyvsp[(14) - (16)].ll_node), (yyvsp[(16) - (16)].ll_node), SMNULL);
                else
                  q = (yyvsp[(14) - (16)].ll_node);                  
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_CREATE_DIR,SMNULL,(yyvsp[(3) - (16)].ll_node),(yyvsp[(8) - (16)].ll_node),q); 
              ;}
    break;

  case 1013:
#line 7122 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1014:
#line 7124 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PARALLEL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1015:
#line 7126 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1016:
#line 7130 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_LOAD_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1017:
#line 7134 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1018:
#line 7136 "gram1.y"
    {
                PTR_LLND q;
                q = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),q,LLNULL);
              ;}
    break;

  case 1019:
#line 7144 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_WAIT_DIR,SMNULL,(yyvsp[(3) - (9)].ll_node),(yyvsp[(8) - (9)].ll_node),LLNULL); ;}
    break;

  case 1047:
#line 7177 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1048:
#line 7183 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1049:
#line 7189 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1050:
#line 7195 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1051:
#line 7201 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1052:
#line 7205 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1062:
#line 7222 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1063:
#line 7227 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1064:
#line 7232 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1065:
#line 7238 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1066:
#line 7244 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1067:
#line 7250 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1068:
#line 7255 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1069:
#line 7261 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1070:
#line 7267 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1071:
#line 7273 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1072:
#line 7280 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1073:
#line 7286 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1074:
#line 7292 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1075:
#line 7299 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1077:
#line 7305 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1078:
#line 7311 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1079:
#line 7318 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1080:
#line 7324 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1081:
#line 7330 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1082:
#line 7336 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1083:
#line 7342 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1084:
#line 7348 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1085:
#line 7354 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1086:
#line 7360 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1087:
#line 7366 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1088:
#line 7372 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1089:
#line 7378 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1090:
#line 7384 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1091:
#line 7394 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1092:
#line 7399 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1093:
#line 7405 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1094:
#line 7409 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1099:
#line 7421 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1100:
#line 7429 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1101:
#line 7435 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1102:
#line 7441 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1103:
#line 7446 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1104:
#line 7452 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1105:
#line 7459 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1106:
#line 7465 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1107:
#line 7469 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1114:
#line 7483 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1115:
#line 7492 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1116:
#line 7496 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1117:
#line 7502 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1118:
#line 7509 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1119:
#line 7516 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1120:
#line 7523 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1121:
#line 7532 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1122:
#line 7538 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1123:
#line 7544 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1124:
#line 7548 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1127:
#line 7558 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1128:
#line 7564 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1129:
#line 7570 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1130:
#line 7574 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1133:
#line 7585 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1134:
#line 7591 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1135:
#line 7597 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1136:
#line 7602 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1137:
#line 7610 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1138:
#line 7616 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1139:
#line 7621 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1140:
#line 7628 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1141:
#line 7632 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1153:
#line 7652 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1154:
#line 7657 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1155:
#line 7662 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1156:
#line 7669 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1157:
#line 7674 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1158:
#line 7680 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1159:
#line 7686 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1160:
#line 7691 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1161:
#line 7696 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1162:
#line 7701 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1163:
#line 7705 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1164:
#line 7710 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1165:
#line 7715 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1166:
#line 7719 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1167:
#line 7724 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1168:
#line 7728 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1169:
#line 7734 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1170:
#line 7739 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1171:
#line 7745 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1172:
#line 7750 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1173:
#line 7756 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1174:
#line 7766 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1175:
#line 7770 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1176:
#line 7774 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1177:
#line 7778 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1178:
#line 7783 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1179:
#line 7786 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1186:
#line 7799 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1187:
#line 7803 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1188:
#line 7807 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1189:
#line 7809 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1190:
#line 7811 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1191:
#line 7815 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1192:
#line 7817 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1193:
#line 7819 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1194:
#line 7823 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1195:
#line 7825 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1196:
#line 7829 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1197:
#line 7831 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1198:
#line 7835 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1199:
#line 7838 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1200:
#line 7841 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1201:
#line 7846 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1202:
#line 7848 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1203:
#line 7850 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1204:
#line 7852 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1205:
#line 7854 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1206:
#line 7858 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1207:
#line 7862 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1208:
#line 7867 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1209:
#line 7871 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1210:
#line 7873 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1211:
#line 7877 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1212:
#line 7879 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1213:
#line 7883 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1214:
#line 7887 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1220:
#line 7898 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1221:
#line 7902 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1222:
#line 7906 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1223:
#line 7910 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1224:
#line 7914 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1225:
#line 7918 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1226:
#line 7920 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1229:
#line 7928 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1230:
#line 7932 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1231:
#line 7936 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1232:
#line 7938 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1236:
#line 7948 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1237:
#line 7952 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1238:
#line 7956 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1239:
#line 7960 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1240:
#line 7962 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1241:
#line 7966 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1242:
#line 7970 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;


/* Line 1267 of yacc.c.  */
#line 13663 "gram1.tab.c"
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



