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
     BINARY_OP = 329,
     UNARY_OP = 330
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
#define BINARY_OP 329
#define UNARY_OP 330




/* Copy the first part of user declarations.  */
#line 328 "gram1.y"

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
#line 409 "gram1.y"
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
#line 849 "gram1.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 611 "gram1.y"

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
#line 1005 "gram1.tab.c"

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
#define YYLAST   5333

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  331
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  509
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1226
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2395

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   330

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
     322,   323,   324,   325,   326,   327,   328,     1,     2,   329,
     330
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
    2121,  2123,  2125,  2127,  2129,  2131,  2133,  2135,  2139,  2148,
    2152,  2155,  2159,  2161,  2165,  2167,  2171,  2173,  2177,  2179,
    2184,  2188,  2190,  2194,  2196,  2200,  2202,  2207,  2212,  2217,
    2221,  2225,  2227,  2231,  2235,  2237,  2241,  2245,  2247,  2251,
    2255,  2257,  2261,  2262,  2268,  2275,  2284,  2286,  2290,  2292,
    2294,  2296,  2301,  2303,  2304,  2307,  2311,  2314,  2319,  2320,
    2322,  2328,  2333,  2340,  2345,  2347,  2352,  2357,  2359,  2366,
    2368,  2372,  2374,  2376,  2381,  2383,  2385,  2389,  2391,  2393,
    2397,  2399,  2400,  2402,  2405,  2409,  2411,  2414,  2420,  2425,
    2430,  2437,  2439,  2443,  2445,  2447,  2454,  2459,  2461,  2465,
    2467,  2469,  2471,  2473,  2475,  2479,  2481,  2483,  2485,  2492,
    2497,  2499,  2504,  2506,  2508,  2510,  2512,  2517,  2520,  2528,
    2530,  2535,  2537,  2549,  2550,  2553,  2557,  2559,  2563,  2565,
    2569,  2571,  2575,  2577,  2581,  2583,  2587,  2589,  2593,  2602,
    2604,  2608,  2611,  2614,  2622,  2624,  2628,  2630,  2634,  2636,
    2641,  2643,  2647,  2649,  2651,  2652,  2654,  2656,  2659,  2661,
    2663,  2665,  2667,  2669,  2671,  2673,  2675,  2677,  2679,  2688,
    2695,  2704,  2711,  2713,  2720,  2727,  2734,  2741,  2743,  2747,
    2753,  2755,  2759,  2768,  2775,  2782,  2787,  2793,  2799,  2802,
    2805,  2806,  2808,  2812,  2814,  2819,  2827,  2829,  2833,  2837,
    2839,  2843,  2849,  2853,  2857,  2859,  2863,  2865,  2867,  2871,
    2875,  2879,  2883,  2894,  2903,  2914,  2915,  2916,  2918,  2921,
    2926,  2931,  2938,  2940,  2942,  2944,  2946,  2948,  2950,  2952,
    2954,  2956,  2958,  2960,  2967,  2972,  2977,  2981,  2991,  2993,
    2995,  2999,  3001,  3007,  3013,  3023,  3024,  3026,  3028,  3032,
    3036,  3040,  3044,  3048,  3055,  3059,  3063,  3067,  3071,  3079,
    3085,  3087,  3089,  3093,  3098,  3100,  3102,  3106,  3108,  3110,
    3114,  3118,  3121,  3125,  3130,  3135,  3141,  3147,  3149,  3152,
    3157,  3162,  3167,  3168,  3170,  3173,  3181,  3188,  3192,  3196,
    3204,  3210,  3212,  3216,  3218,  3223,  3226,  3230,  3234,  3239,
    3246,  3250,  3253,  3257,  3259,  3261,  3266,  3272,  3276,  3283,
    3286,  3291,  3294,  3296,  3300,  3304,  3305,  3307,  3310,  3313,
    3316,  3319,  3329,  3335,  3337,  3341,  3344,  3347,  3350,  3360,
    3365,  3367,  3371,  3373,  3375,  3378,  3379,  3387,  3389,  3394,
    3396,  3400,  3402,  3404,  3406,  3408,  3410,  3412,  3414,  3416,
    3418,  3420,  3422,  3424,  3426,  3428,  3430,  3432,  3434,  3436,
    3438,  3440,  3442,  3444,  3446,  3448,  3450,  3452,  3454,  3456,
    3458,  3460,  3463,  3466,  3471,  3475,  3480,  3486,  3488,  3490,
    3492,  3494,  3496,  3498,  3500,  3502,  3504,  3510,  3513,  3516,
    3519,  3522,  3525,  3531,  3533,  3535,  3537,  3542,  3547,  3552,
    3557,  3559,  3561,  3563,  3565,  3567,  3569,  3571,  3573,  3575,
    3577,  3579,  3581,  3583,  3585,  3587,  3592,  3596,  3601,  3607,
    3609,  3611,  3613,  3615,  3620,  3624,  3627,  3632,  3636,  3641,
    3645,  3650,  3656,  3658,  3660,  3662,  3664,  3666,  3668,  3670,
    3678,  3684,  3686,  3688,  3690,  3692,  3697,  3701,  3706,  3712,
    3714,  3716,  3721,  3725,  3730,  3736,  3738,  3740,  3743,  3745,
    3748,  3753,  3757,  3762,  3766,  3771,  3777,  3779,  3781,  3783,
    3785,  3787,  3789,  3791,  3793,  3795,  3797,  3799,  3802,  3807,
    3811,  3814,  3819,  3823,  3826,  3830,  3833,  3836,  3839,  3842,
    3845,  3848,  3852,  3855,  3861,  3864,  3870,  3873,  3879,  3881,
    3883,  3887,  3891,  3892,  3893,  3895,  3897,  3899,  3901,  3903,
    3905,  3909,  3912,  3918,  3923,  3926,  3932,  3937,  3940,  3943,
    3945,  3947,  3951,  3954,  3957,  3960,  3965,  3970,  3975,  3980,
    3985,  3990,  3992,  3994,  3996,  4000,  4003,  4006,  4008,  4010,
    4012,  4014,  4016,  4018,  4020,  4025,  4030,  4035,  4038,  4040,
    4042,  4046,  4048,  4050,  4056,  4062,  4064,  4068,  4070,  4072,
    4074,  4080,  4086,  4092,  4094,  4098,  4101
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     332,     0,    -1,    -1,   332,   333,   116,    -1,   334,   335,
     551,    -1,   334,   352,   551,    -1,   334,   497,   551,    -1,
     334,   133,   348,    -1,   334,   247,    -1,   257,    -1,     1,
      -1,   150,    -1,   193,   336,   343,    -1,    57,   336,   344,
      -1,   233,   336,   338,   345,    -1,   337,   233,   336,   338,
     345,    -1,   124,   336,   339,   345,   341,    -1,   340,   345,
     341,    -1,   114,   342,   345,   341,    -1,   164,   336,   342,
      -1,    -1,   202,   349,    -1,   195,   349,    -1,    95,   349,
      -1,   342,    -1,   342,    -1,   373,   124,   336,   342,    -1,
     373,   337,   124,   336,   342,    -1,   337,   124,   336,   342,
      -1,   337,   373,   124,   336,   342,    -1,   349,   350,    -1,
     349,   213,    15,   342,    21,    -1,   129,    -1,    -1,   342,
      -1,    -1,   342,    -1,    -1,    15,    21,    -1,    15,   346,
      21,    -1,   347,    -1,   346,     8,   347,    -1,   342,    -1,
       5,    -1,    64,    -1,    -1,    -1,    -1,   357,    -1,   358,
      -1,   359,    -1,   389,    -1,   385,    -1,   552,    -1,   394,
      -1,   395,    -1,   396,    -1,   454,    -1,   375,    -1,   390,
      -1,   400,    -1,   216,   464,    -1,   216,   464,   465,   431,
      -1,   123,   463,    -1,   183,   464,    15,   437,    21,    -1,
     365,    -1,   366,    -1,   371,    -1,   368,    -1,   370,    -1,
     386,    -1,   387,    -1,   388,    -1,   353,    -1,   441,    -1,
     439,    -1,   367,    -1,   142,   464,    -1,   142,   464,   342,
      -1,   141,   464,    15,   355,    21,    -1,   140,   464,    15,
      26,    21,    -1,   107,   506,    -1,    10,    -1,   354,    -1,
     356,    -1,    17,    -1,    16,    -1,     5,    -1,     9,    -1,
      37,    -1,    23,    -1,    22,    -1,    35,    -1,    38,    -1,
      34,    -1,    25,    -1,    32,    -1,    29,    -1,    28,    -1,
      31,    -1,    30,    -1,    33,    -1,    24,    -1,   245,   464,
     465,   342,    -1,   245,     8,   464,   349,   364,   465,   342,
      -1,   112,   464,    -1,   112,   464,   342,    -1,   373,   360,
     342,   464,   447,   379,   384,    -1,   359,     8,   342,   447,
     379,   384,    -1,    -1,     7,     7,    -1,     8,   349,   361,
       7,     7,    -1,   362,    -1,   361,     8,   349,   362,    -1,
     183,    -1,   364,    -1,    44,    -1,    87,   447,    -1,   119,
      -1,   145,    15,   363,    21,    -1,   143,    -1,   178,    -1,
     187,    -1,   216,    -1,   230,    -1,   236,    -1,   349,   148,
      -1,   349,   180,    -1,   349,   147,    -1,   194,    -1,   191,
      -1,   145,   464,    15,   363,    21,   465,   342,    -1,   365,
       8,   342,    -1,   178,   464,   465,   342,    -1,   366,     8,
     342,    -1,   230,   464,   465,   393,    -1,   367,     8,   393,
      -1,   191,   464,    -1,   191,   464,   465,   369,   433,    -1,
      -1,   219,   464,    -1,   194,   464,    -1,   194,   464,   465,
     372,   433,    -1,    -1,   377,   374,   381,   374,    -1,   244,
      15,   342,    21,   374,    -1,    -1,   376,   342,    -1,   375,
       8,   342,    -1,    13,    -1,     6,    -1,   378,    -1,   144,
      -1,   200,    -1,    68,    -1,    90,    -1,    91,    -1,   154,
      -1,    63,    -1,    -1,   380,    -1,     5,   527,   484,   528,
     374,    -1,     5,   527,    15,   528,     5,    21,    -1,     5,
     527,    15,   528,   470,    21,    -1,    -1,   380,    -1,    15,
     547,   382,   383,    21,    -1,    15,   547,   382,   383,     8,
     547,   382,   383,    21,    -1,   470,    -1,     5,    -1,   538,
     470,    -1,   538,     5,    -1,    -1,    -1,    26,   470,    -1,
      18,   470,    -1,    87,   465,   464,   342,   447,    -1,   385,
       8,   342,   447,    -1,    44,   464,   465,   393,    -1,   386,
       8,   393,    -1,   187,   464,   465,   393,    -1,   387,     8,
     393,    -1,   236,   464,   465,   393,    -1,   388,     8,   393,
      -1,    67,   464,   393,    -1,    67,   464,   392,   393,    -1,
     389,   521,   392,   521,   393,    -1,   389,     8,   393,    -1,
     167,   464,   391,   473,    -1,   390,   521,   391,   521,   473,
      -1,   390,     8,   473,    -1,    37,   342,    37,    -1,    23,
      -1,    37,   342,    37,    -1,   342,   447,    -1,   119,   464,
     465,   342,    -1,   394,     8,   342,    -1,   143,   464,   465,
     342,    -1,   395,     8,   342,    -1,   117,   464,   397,    -1,
     396,     8,   397,    -1,    15,   398,    21,    -1,   399,     8,
     399,    -1,   398,     8,   399,    -1,   342,    -1,   342,    15,
     469,    21,    -1,   478,    -1,   401,    -1,    80,   463,   402,
     404,    -1,   401,   521,   404,    -1,    -1,    -1,   405,    37,
     406,    37,    -1,   407,    -1,   405,     8,   407,    -1,   418,
      -1,   406,     8,   418,    -1,   408,   410,    -1,   408,   410,
     411,    -1,   408,   410,   412,    -1,   408,   410,   411,   412,
      -1,   408,   415,    -1,    -1,   342,    -1,   342,    -1,    15,
     413,    21,    -1,    15,   414,     7,   414,    21,    -1,   427,
      -1,   413,     8,   427,    -1,    -1,   427,    -1,    15,   416,
       8,   409,    26,   413,    21,    -1,   417,    -1,   416,     8,
     417,    -1,   410,   411,    -1,   410,   412,    -1,   410,   411,
     412,    -1,   415,    -1,   419,    -1,   408,   409,     5,   419,
      -1,   422,     5,   419,    -1,   408,   409,    -1,   421,    -1,
     423,    -1,   425,    -1,    36,    -1,    36,   246,   487,    -1,
      27,    -1,    27,   246,   487,    -1,    64,    -1,   420,    -1,
     408,   473,    15,   547,   466,    21,    -1,    59,    -1,   422,
      -1,    17,   422,    -1,    16,   422,    -1,   149,    -1,   149,
     246,   487,    -1,   424,    -1,    17,   424,    -1,    16,   424,
      -1,   201,    -1,   201,   246,   487,    -1,    92,    -1,    92,
     246,   487,    -1,    15,   426,     8,   426,    21,    -1,   423,
      -1,   421,    -1,   428,    -1,    17,   428,    -1,    16,   428,
      -1,   427,    17,   428,    -1,   427,    16,   428,    -1,   429,
      -1,   428,     5,   429,    -1,   428,    37,   429,    -1,   430,
      -1,   430,     9,   429,    -1,   149,    -1,   409,    -1,    15,
     427,    21,    -1,   432,    -1,   431,     8,   432,    -1,   393,
      -1,   392,    -1,   434,   436,   435,    -1,   433,     8,   434,
     436,   435,    -1,    -1,    -1,   342,    -1,   177,    15,   355,
      21,    -1,    47,    15,    26,    21,    -1,   438,    -1,   437,
       8,   438,    -1,   342,    26,   470,    -1,   163,   440,    -1,
     342,    -1,   440,     8,   342,    -1,   248,   464,   442,    -1,
     248,   464,   442,     8,   351,   445,    -1,   248,   464,   442,
       8,   351,   172,    -1,   248,   464,   442,     8,   351,   172,
     443,    -1,   342,    -1,   444,    -1,   443,     8,   444,    -1,
     342,    18,   342,    -1,   342,    -1,   446,    -1,   445,     8,
     446,    -1,   342,    18,   342,    -1,    -1,    15,   448,    21,
      -1,    -1,   449,   450,    -1,   448,     8,   450,    -1,   451,
      -1,     7,    -1,   470,     7,    -1,   470,     7,   451,    -1,
       5,    -1,   470,    -1,   453,    -1,   452,     8,   453,    -1,
     149,    -1,   130,   464,   455,    -1,   131,    -1,   456,    -1,
     455,     8,   456,    -1,   457,    15,   460,    21,    -1,    -1,
     458,   459,    -1,   231,   378,    -1,   373,    -1,   461,    -1,
     460,     8,   461,    -1,   462,    -1,   462,    16,   462,    -1,
     129,    -1,    -1,    -1,    -1,     7,     7,    -1,    -1,   468,
      -1,   470,    -1,   488,    -1,   538,   470,    -1,   547,   467,
      -1,   468,     8,   547,   467,    -1,   470,    -1,   469,     8,
     470,    -1,   471,    -1,    15,   470,    21,    -1,   486,    -1,
     474,    -1,   482,    -1,   489,    -1,   470,    17,   470,    -1,
     470,    16,   470,    -1,   470,     5,   470,    -1,   470,    37,
     470,    -1,   470,     9,   470,    -1,   354,   470,    -1,    17,
     470,    -1,    16,   470,    -1,   470,    25,   470,    -1,   470,
      29,   470,    -1,   470,    31,   470,    -1,   470,    28,   470,
      -1,   470,    30,   470,    -1,   470,    32,   470,    -1,   470,
      24,   470,    -1,   470,    33,   470,    -1,   470,    38,   470,
      -1,   470,    35,   470,    -1,   470,    22,   470,    -1,    34,
     470,    -1,   470,    23,   470,    -1,   470,   354,   470,    -1,
      17,    -1,    16,    -1,   342,    -1,   473,    -1,   476,    -1,
     475,    -1,   473,    15,   547,   466,    21,    -1,   473,    15,
     547,   466,    21,   480,    -1,   476,    15,   466,    21,    -1,
     476,    15,   466,    21,   480,    -1,   474,     3,   129,    -1,
     473,    -1,   476,    -1,   473,    15,   547,   466,    21,    -1,
     476,    15,   466,    21,    -1,   473,   480,    -1,    -1,   480,
      -1,    15,   481,     7,   481,    21,    -1,    -1,   470,    -1,
     483,    -1,   483,   246,   487,    -1,   484,    -1,   484,   246,
     487,    -1,   485,   479,    -1,    36,    -1,    27,    -1,   201,
      -1,    92,    -1,   149,    -1,    64,    -1,   473,   246,    64,
      -1,   484,   246,    64,    -1,    15,   471,     8,   471,    21,
      -1,   473,    -1,   484,    -1,   470,     7,   470,    -1,   470,
       7,    -1,   470,     7,   470,     7,   470,    -1,   470,     7,
       7,   470,    -1,     7,   470,     7,   470,    -1,     7,     7,
     470,    -1,     7,   470,    -1,     7,    -1,    -1,    -1,    14,
     383,   490,   544,   491,    20,    -1,   473,    -1,   476,    -1,
     477,    -1,   493,     8,   547,   477,    -1,   493,     8,   547,
     538,   473,    -1,   492,    -1,   494,     8,   547,   492,    -1,
     494,     8,   547,   538,   473,    -1,    -1,   473,    -1,   496,
       8,   473,    -1,   518,    -1,   517,    -1,   500,    -1,   508,
     500,    -1,   102,   526,   506,    -1,   103,   526,   505,    -1,
     108,   506,    -1,   498,    -1,   508,   498,    -1,   509,   518,
      -1,   509,   239,    -1,   508,   509,   239,    -1,    97,   526,
      15,   470,    21,   239,   505,    -1,    96,   526,   505,    -1,
     106,   526,   505,    -1,   501,    -1,    76,   526,    -1,   510,
     518,    -1,   510,    -1,   508,   510,    -1,   105,   526,   505,
      -1,   553,    -1,   806,    -1,   822,    -1,    89,   526,    15,
     470,    21,    -1,    89,   526,   527,   516,   528,   587,   499,
      -1,    -1,     8,   349,   254,    15,   470,    21,    -1,   254,
      15,   470,    21,    -1,   185,   526,   527,   516,   528,   521,
     514,    26,   470,     8,   470,    -1,   185,   526,   527,   516,
     528,   521,   514,    26,   470,     8,   470,     8,   470,    -1,
      62,   526,   502,   505,    -1,    84,   526,   505,    -1,   110,
     526,   505,    -1,   218,   526,   349,    62,    15,   470,    21,
      -1,   508,   218,   526,   349,    62,    15,   470,    21,    -1,
      15,   504,    21,    -1,   470,    -1,   470,     7,    -1,     7,
     470,    -1,   470,     7,   470,    -1,   503,    -1,   504,     8,
     503,    -1,    -1,   342,    -1,    -1,   342,    -1,    75,    -1,
     507,     7,    -1,   155,   526,    15,   470,    21,    -1,   122,
     526,    15,   511,   513,    21,    -1,   512,    -1,   511,     8,
     512,    -1,   514,    26,   488,    -1,    -1,     8,   470,    -1,
     342,    -1,   514,    26,   470,     8,   470,    -1,   514,    26,
     470,     8,   470,     8,   470,    -1,    -1,   149,    -1,   113,
     526,   505,    -1,    98,   526,   505,    -1,    98,   526,    15,
     470,    21,   505,    -1,   252,   526,    15,   470,    21,    -1,
     508,   252,   526,    15,   470,    21,    -1,   519,   470,    26,
     470,    -1,   188,   526,   474,    18,   470,    -1,    48,   526,
     453,   240,   342,    -1,    77,   526,    -1,   520,    -1,   529,
      -1,    46,   526,    15,   470,    21,   453,     8,   453,     8,
     453,    -1,   522,    -1,   522,    15,    21,    -1,   522,    15,
     523,    21,    -1,   214,   526,   481,    -1,   525,   526,   481,
      -1,    79,   526,   505,    -1,   115,   526,   505,    -1,    45,
     526,    15,   495,   493,    21,    -1,    81,   526,    15,   495,
     494,    21,    -1,   170,   526,    15,   496,    21,    -1,   253,
     526,    15,   470,    21,   474,    26,   470,    -1,   152,   403,
      -1,   186,   526,   453,    -1,    49,   526,   342,    -1,    49,
     526,   342,   521,    15,   452,    21,    -1,    69,   526,    15,
     452,    21,   521,   470,    -1,    -1,     8,    -1,    61,   526,
     342,   547,    -1,   547,   524,    -1,   523,     8,   547,   524,
      -1,   470,    -1,   538,   470,    -1,     5,   453,    -1,   184,
      -1,   232,    -1,    -1,    -1,    -1,   530,   535,    -1,   530,
     550,    -1,   530,     5,    -1,   530,     9,    -1,   532,   535,
      -1,   539,   535,    -1,   539,   534,    -1,   539,   535,   542,
      -1,   539,   534,     8,   542,    -1,   540,   535,    -1,   540,
     535,   544,    -1,   541,    -1,   541,     8,   544,    -1,   531,
     526,   548,    -1,    53,    -1,   215,    -1,   104,    -1,   533,
     526,   548,    -1,   139,    -1,   176,    -1,    66,    -1,   550,
      -1,     5,    -1,    15,   549,    21,    -1,    15,   536,    21,
      -1,   537,    -1,   536,     8,   547,   537,    -1,   549,    -1,
       5,    -1,     9,    -1,   538,   470,    -1,   538,     5,    -1,
     538,     9,    -1,   166,    -1,   197,   526,   548,    -1,   256,
     526,   548,    -1,   190,   526,   549,   548,    -1,   190,   526,
       5,   548,    -1,   543,    -1,   542,     8,   543,    -1,   474,
      -1,    15,   542,     8,   515,    21,    -1,   471,    -1,   546,
      -1,   545,    -1,   471,     8,   471,    -1,   471,     8,   546,
      -1,   546,     8,   471,    -1,   546,     8,   546,    -1,   545,
       8,   471,    -1,   545,     8,   546,    -1,   486,    -1,    15,
     470,    21,    -1,    15,   471,     8,   515,    21,    -1,    15,
     546,     8,   515,    21,    -1,    15,   545,     8,   515,    21,
      -1,    -1,    -1,   550,    -1,    15,   549,    21,    -1,   474,
      -1,   482,    -1,   549,   472,   549,    -1,   549,     5,   549,
      -1,   549,    37,   549,    -1,   549,     9,   549,    -1,   472,
     549,    -1,   549,    23,   549,    -1,   129,    26,   470,    -1,
      -1,   257,    -1,   554,    -1,   602,    -1,   577,    -1,   556,
      -1,   567,    -1,   562,    -1,   614,    -1,   617,    -1,   693,
      -1,   559,    -1,   568,    -1,   570,    -1,   572,    -1,   574,
      -1,   622,    -1,   628,    -1,   625,    -1,   743,    -1,   741,
      -1,   578,    -1,   603,    -1,   632,    -1,   682,    -1,   680,
      -1,   681,    -1,   683,    -1,   684,    -1,   685,    -1,   686,
      -1,   687,    -1,   695,    -1,   697,    -1,   702,    -1,   699,
      -1,   701,    -1,   705,    -1,   703,    -1,   704,    -1,   716,
      -1,   720,    -1,   721,    -1,   723,    -1,   724,    -1,   725,
      -1,   726,    -1,   727,    -1,   631,    -1,   710,    -1,   711,
      -1,   712,    -1,   715,    -1,   728,    -1,   731,    -1,   736,
      -1,   708,    -1,   742,    -1,    82,   464,   555,    -1,    82,
     464,     8,   349,    67,     7,     7,   555,    -1,   554,     8,
     555,    -1,   342,   447,    -1,    94,   464,   557,    -1,   558,
      -1,   557,     8,   558,    -1,   342,    -1,   138,   464,   560,
      -1,   561,    -1,   560,     8,   561,    -1,   342,    -1,   228,
     464,   566,   563,    -1,    15,   564,    21,    -1,   565,    -1,
     564,     8,   565,    -1,   470,    -1,   470,     7,   470,    -1,
     342,    -1,   259,   464,   342,   447,    -1,   303,   464,   342,
     447,    -1,   567,     8,   342,   447,    -1,   136,   464,   569,
      -1,   568,     8,   569,    -1,   342,    -1,   211,   464,   571,
      -1,   570,     8,   571,    -1,   342,    -1,   205,   464,   573,
      -1,   572,     8,   573,    -1,   342,    -1,    70,   464,   575,
      -1,   574,     8,   575,    -1,   342,    -1,   175,   342,   447,
      -1,    -1,    88,   464,   581,   584,   576,    -1,   204,   526,
     581,   585,   587,   576,    -1,   204,   526,   585,   587,   576,
       7,     7,   579,    -1,   580,    -1,   579,     8,   580,    -1,
     581,    -1,   582,    -1,   342,    -1,   342,    15,   469,    21,
      -1,   342,    -1,    -1,   585,   587,    -1,    15,   586,    21,
      -1,   587,   588,    -1,   586,     8,   587,   588,    -1,    -1,
      58,    -1,    58,    15,   547,   601,    21,    -1,   126,    15,
     589,    21,    -1,   258,    15,   589,     8,   470,    21,    -1,
     165,    15,   470,    21,    -1,     5,    -1,   137,    15,   589,
      21,    -1,    86,    15,   590,    21,    -1,   342,    -1,    15,
     591,    21,   349,   255,   593,    -1,   592,    -1,   591,     8,
     592,    -1,   470,    -1,   594,    -1,   594,    15,   595,    21,
      -1,   342,    -1,   596,    -1,   595,     8,   596,    -1,   470,
      -1,   740,    -1,    40,   597,   598,    -1,   342,    -1,    -1,
     599,    -1,    17,   600,    -1,   598,    17,   600,    -1,   470,
      -1,   538,   470,    -1,   538,   470,     8,   538,   470,    -1,
      43,   464,   605,   607,    -1,   199,   526,   606,   607,    -1,
     199,   526,   607,     7,     7,   604,    -1,   606,    -1,   604,
       8,   606,    -1,   342,    -1,   473,    -1,    15,   612,    21,
     349,   255,   608,    -1,   611,    15,   609,    21,    -1,   610,
      -1,   609,     8,   610,    -1,   470,    -1,     5,    -1,   488,
      -1,   342,    -1,   613,    -1,   612,     8,   613,    -1,   342,
      -1,     5,    -1,     7,    -1,   615,     7,     7,   464,   342,
     447,    -1,   614,     8,   342,   447,    -1,   616,    -1,   615,
       8,   349,   616,    -1,    82,    -1,   259,    -1,   303,    -1,
      94,    -1,    87,    15,   448,    21,    -1,   228,   563,    -1,
      43,    15,   612,    21,   349,   255,   608,    -1,    43,    -1,
      88,   585,   587,   576,    -1,    88,    -1,   373,     8,   349,
      93,   464,    15,   618,    21,     7,     7,   620,    -1,    -1,
     619,     7,    -1,   618,     8,     7,    -1,   621,    -1,   620,
       8,   621,    -1,   342,    -1,   127,   464,   623,    -1,   624,
      -1,   623,     8,   624,    -1,   342,    -1,    74,   464,   626,
      -1,   627,    -1,   626,     8,   627,    -1,   342,    -1,    51,
     464,   629,    -1,    51,   464,     8,   349,    67,     7,     7,
     629,    -1,   630,    -1,   629,     8,   630,    -1,   342,   447,
      -1,   168,   526,    -1,   182,   526,    15,   633,    21,   635,
     639,    -1,   634,    -1,   633,     8,   634,    -1,   473,    -1,
     587,   173,   636,    -1,   587,    -1,   473,    15,   637,    21,
      -1,   638,    -1,   637,     8,   638,    -1,   470,    -1,     5,
      -1,    -1,   640,    -1,   641,    -1,   640,   641,    -1,   645,
      -1,   665,    -1,   673,    -1,   642,    -1,   650,    -1,   652,
      -1,   651,    -1,   643,    -1,   646,    -1,   647,    -1,     8,
     349,   209,    15,   688,     7,   689,    21,    -1,     8,   349,
     209,    15,   689,    21,    -1,     8,   349,    71,    15,   644,
       7,   689,    21,    -1,     8,   349,    71,    15,   689,    21,
      -1,   342,    -1,     8,   349,   169,    15,   649,    21,    -1,
       8,   349,   282,    15,   649,    21,    -1,     8,   349,   191,
      15,   649,    21,    -1,     8,   349,   320,    15,   648,    21,
      -1,   470,    -1,   470,     8,   470,    -1,   470,     8,   470,
       8,   470,    -1,   474,    -1,   649,     8,   474,    -1,     8,
     349,   135,    15,   688,     7,   706,    21,    -1,     8,   349,
     135,    15,   706,    21,    -1,     8,   349,   229,    15,   470,
      21,    -1,     8,   349,    41,   653,    -1,     8,   349,    41,
     653,   653,    -1,    15,   587,   654,   655,    21,    -1,   148,
       7,    -1,   180,     7,    -1,    -1,   656,    -1,   655,     8,
     656,    -1,   678,    -1,   678,    15,   657,    21,    -1,   678,
      15,   657,    21,    15,   659,    21,    -1,   658,    -1,   657,
       8,   658,    -1,   470,     7,   470,    -1,   660,    -1,   659,
       8,   660,    -1,   661,     7,   662,     7,   663,    -1,   661,
       7,   662,    -1,   661,     7,   663,    -1,   661,    -1,   662,
       7,   663,    -1,   662,    -1,   663,    -1,   349,   217,   664,
      -1,   349,   157,   664,    -1,   349,   128,   664,    -1,    15,
     468,    21,    -1,     8,   349,   208,    15,   666,   670,   667,
       8,   669,    21,    -1,     8,   349,   208,    15,   666,   670,
     667,    21,    -1,     8,   349,   208,    15,   666,   668,   667,
       7,   669,    21,    -1,    -1,    -1,   342,    -1,   349,   670,
      -1,   669,     8,   349,   670,    -1,   671,    15,   474,    21,
      -1,   672,    15,   649,     8,   470,    21,    -1,   234,    -1,
     192,    -1,   162,    -1,   159,    -1,    35,    -1,    22,    -1,
      24,    -1,    33,    -1,   247,    -1,   158,    -1,   161,    -1,
       8,   349,   223,    15,   675,    21,    -1,     8,   349,   224,
     674,    -1,     8,   349,   226,   674,    -1,     8,   349,   221,
      -1,     8,   349,   221,    15,   678,    15,   564,    21,    21,
      -1,   342,    -1,   676,    -1,   675,     8,   676,    -1,   678,
      -1,   678,    15,   677,    78,    21,    -1,   678,    15,   677,
     564,    21,    -1,   678,    15,   677,   564,    21,    15,   349,
      78,    21,    -1,    -1,   473,    -1,   678,    -1,   679,     8,
     678,    -1,   225,   526,   674,    -1,   224,   526,   674,    -1,
     227,   526,   674,    -1,   226,   526,   674,    -1,   222,   526,
     674,    15,   675,    21,    -1,   206,   526,   668,    -1,   207,
     526,   668,    -1,    72,   526,   644,    -1,    73,   526,   644,
      -1,   210,   526,    15,   688,     7,   689,    21,    -1,   210,
     526,    15,   689,    21,    -1,   342,    -1,   690,    -1,   689,
       8,   690,    -1,   678,    15,   691,    21,    -1,   678,    -1,
     692,    -1,   691,     8,   692,    -1,   470,    -1,     7,    -1,
     237,   464,   694,    -1,   693,     8,   694,    -1,   342,   447,
      -1,   238,   526,   696,    -1,   238,   526,   696,   665,    -1,
     238,   526,   696,   643,    -1,   238,   526,   696,   665,   643,
      -1,   238,   526,   696,   643,   665,    -1,   342,    -1,   111,
     526,    -1,   696,    15,   470,    21,    -1,   696,    15,   488,
      21,    -1,   174,   526,   475,   700,    -1,    -1,   645,    -1,
     109,   526,    -1,   160,   526,   698,   349,   175,   583,   447,
      -1,   160,   526,   698,   349,   321,   474,    -1,   189,   526,
     688,    -1,   212,   526,   688,    -1,   135,   526,    15,   688,
       7,   706,    21,    -1,   135,   526,    15,   706,    21,    -1,
     707,    -1,   706,     8,   707,    -1,   678,    -1,   678,    15,
     469,    21,    -1,   134,   526,    -1,   134,   526,   645,    -1,
     134,   526,   709,    -1,   134,   526,   645,   709,    -1,     8,
     349,   208,    15,   649,    21,    -1,    50,   526,   714,    -1,
      99,   526,    -1,    52,   526,   714,    -1,   342,    -1,   713,
      -1,   713,    15,   469,    21,    -1,   120,   526,   474,    26,
     474,    -1,    83,   526,   719,    -1,    83,   526,   719,    15,
     717,    21,    -1,   547,   718,    -1,   717,     8,   547,   718,
      -1,   538,   470,    -1,   149,    -1,   100,   526,   719,    -1,
     146,   526,   722,    -1,    -1,   470,    -1,   101,   526,    -1,
     241,   526,    -1,   242,   526,    -1,    56,   526,    -1,    65,
     526,   547,    15,   523,    21,   383,   465,   649,    -1,   322,
     526,    15,   729,    21,    -1,   730,    -1,   729,     8,   730,
      -1,   349,   315,    -1,   349,   318,    -1,   349,   182,    -1,
     220,   526,    15,   732,    26,   600,    21,   587,   735,    -1,
     473,    15,   733,    21,    -1,   734,    -1,   733,     8,   734,
      -1,   590,    -1,   740,    -1,   132,   679,    -1,    -1,   153,
     526,    15,   473,    18,   737,    21,    -1,   473,    -1,   473,
      15,   738,    21,    -1,   739,    -1,   738,     8,   739,    -1,
     740,    -1,     7,    -1,     5,    -1,   792,    -1,   745,    -1,
     744,    -1,   762,    -1,   765,    -1,   766,    -1,   767,    -1,
     768,    -1,   774,    -1,   777,    -1,   782,    -1,   783,    -1,
     784,    -1,   787,    -1,   788,    -1,   789,    -1,   790,    -1,
     791,    -1,   793,    -1,   794,    -1,   795,    -1,   796,    -1,
     797,    -1,   798,    -1,   799,    -1,   800,    -1,   801,    -1,
     268,   526,    -1,   275,   526,    -1,   291,   526,   587,   746,
      -1,   291,   526,   587,    -1,   521,   587,   747,   587,    -1,
     746,   521,   587,   747,   587,    -1,   749,    -1,   758,    -1,
     753,    -1,   754,    -1,   750,    -1,   751,    -1,   752,    -1,
     756,    -1,   757,    -1,   804,    15,   805,   803,    21,    -1,
     191,   748,    -1,   282,   748,    -1,   285,   748,    -1,   265,
     748,    -1,   299,   748,    -1,    84,    15,   349,   755,    21,
      -1,   191,    -1,   299,    -1,   288,    -1,   304,    15,   470,
      21,    -1,   289,    15,   470,    21,    -1,   208,    15,   759,
      21,    -1,   587,   761,     7,   760,    -1,   649,    -1,    17,
      -1,    16,    -1,     5,    -1,    37,    -1,   162,    -1,   159,
      -1,    35,    -1,    22,    -1,    24,    -1,    33,    -1,   305,
      -1,   306,    -1,   307,    -1,   247,    -1,   297,   526,   587,
     763,    -1,   297,   526,   587,    -1,   521,   587,   764,   587,
      -1,   763,   521,   587,   764,   587,    -1,   749,    -1,   758,
      -1,   750,    -1,   751,    -1,   279,   526,   587,   781,    -1,
     279,   526,   587,    -1,   296,   526,    -1,   269,   526,   587,
     769,    -1,   269,   526,   587,    -1,   272,   526,   587,   781,
      -1,   272,   526,   587,    -1,   521,   587,   770,   587,    -1,
     769,   521,   587,   770,   587,    -1,   749,    -1,   758,    -1,
     750,    -1,   751,    -1,   772,    -1,   771,    -1,   290,    -1,
     298,    15,   349,   773,     8,   470,    21,    -1,   298,    15,
     349,   773,    21,    -1,   230,    -1,    94,    -1,   284,    -1,
     295,    -1,   300,   526,   587,   775,    -1,   300,   526,   587,
      -1,   521,   587,   776,   587,    -1,   775,   521,   587,   776,
     587,    -1,   749,    -1,   750,    -1,   280,   526,   587,   778,
      -1,   280,   526,   587,    -1,   521,   587,   779,   587,    -1,
     778,   521,   587,   779,   587,    -1,   781,    -1,   780,    -1,
     266,   748,    -1,   287,    -1,   302,   526,    -1,   281,   526,
     587,   781,    -1,   281,   526,   587,    -1,   292,   526,   587,
     785,    -1,   292,   526,   587,    -1,   521,   587,   786,   587,
      -1,   785,   521,   587,   786,   587,    -1,   749,    -1,   758,
      -1,   753,    -1,   754,    -1,   750,    -1,   751,    -1,   752,
      -1,   756,    -1,   757,    -1,   772,    -1,   771,    -1,   276,
     526,    -1,   293,   526,   587,   746,    -1,   293,   526,   587,
      -1,   277,   526,    -1,   294,   526,   587,   746,    -1,   294,
     526,   587,    -1,   278,   526,    -1,   301,   464,   748,    -1,
     286,   526,    -1,   273,   526,    -1,   290,   526,    -1,   274,
     526,    -1,   264,   526,    -1,   263,   526,    -1,   283,   526,
     748,    -1,   283,   526,    -1,   267,   526,    15,   473,    21,
      -1,   267,   526,    -1,   271,   526,    15,   473,    21,    -1,
     271,   526,    -1,    37,   342,   804,    37,   805,    -1,   802,
      -1,   473,    -1,   803,     8,   802,    -1,   803,     8,   473,
      -1,    -1,    -1,   807,    -1,   820,    -1,   808,    -1,   821,
      -1,   809,    -1,   810,    -1,   308,   526,   811,    -1,   310,
     526,    -1,   312,   526,    15,   817,    21,    -1,   312,   526,
      15,    21,    -1,   312,   526,    -1,   313,   526,    15,   817,
      21,    -1,   313,   526,    15,    21,    -1,   313,   526,    -1,
     349,   350,    -1,   812,    -1,   813,    -1,   812,     8,   813,
      -1,   349,   814,    -1,   349,   816,    -1,   349,   815,    -1,
     147,    15,   817,    21,    -1,   148,    15,   817,    21,    -1,
     180,    15,   817,    21,    -1,   318,    15,   817,    21,    -1,
     319,    15,   817,    21,    -1,   314,    15,   818,    21,    -1,
     315,    -1,   649,    -1,   819,    -1,   818,     8,   819,    -1,
     349,   316,    -1,   349,   317,    -1,   309,    -1,   311,    -1,
     823,    -1,   824,    -1,   825,    -1,   826,    -1,   827,    -1,
     323,    15,   828,    21,    -1,   324,    15,   832,    21,    -1,
     325,    15,   837,    21,    -1,   327,   839,    -1,   328,    -1,
     829,    -1,   828,     8,   829,    -1,   830,    -1,   831,    -1,
     349,   208,    15,   669,    21,    -1,   349,   191,    15,   649,
      21,    -1,   833,    -1,   832,     8,   833,    -1,   834,    -1,
     835,    -1,   836,    -1,   349,   228,    15,   675,    21,    -1,
     349,    41,    15,   675,    21,    -1,   349,   209,    15,   689,
      21,    -1,   838,    -1,   837,     8,   838,    -1,   349,   326,
      -1,   342,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   756,   756,   757,   761,   763,   777,   808,   817,   823,
     843,   852,   868,   880,   890,   897,   903,   908,   913,   937,
     964,   978,   980,   982,   986,  1003,  1017,  1041,  1057,  1071,
    1089,  1091,  1098,  1102,  1103,  1110,  1111,  1119,  1120,  1122,
    1126,  1127,  1131,  1135,  1141,  1151,  1155,  1160,  1167,  1168,
    1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,
    1179,  1180,  1185,  1190,  1197,  1199,  1200,  1201,  1202,  1203,
    1204,  1205,  1206,  1207,  1208,  1209,  1210,  1213,  1217,  1225,
    1233,  1242,  1250,  1254,  1256,  1260,  1262,  1264,  1266,  1268,
    1270,  1272,  1274,  1276,  1278,  1280,  1282,  1284,  1286,  1288,
    1290,  1292,  1294,  1299,  1308,  1318,  1326,  1336,  1357,  1377,
    1378,  1380,  1384,  1386,  1390,  1394,  1396,  1400,  1406,  1410,
    1412,  1416,  1420,  1424,  1428,  1432,  1438,  1442,  1446,  1452,
    1457,  1464,  1475,  1488,  1499,  1512,  1522,  1535,  1540,  1547,
    1550,  1555,  1560,  1567,  1570,  1580,  1594,  1597,  1616,  1643,
    1645,  1657,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1676,
    1677,  1681,  1683,  1690,  1695,  1696,  1698,  1700,  1713,  1719,
    1725,  1734,  1743,  1756,  1757,  1760,  1764,  1779,  1794,  1812,
    1833,  1853,  1875,  1892,  1910,  1917,  1924,  1931,  1944,  1951,
    1958,  1969,  1973,  1975,  1980,  1998,  2009,  2021,  2033,  2047,
    2053,  2060,  2066,  2072,  2080,  2087,  2103,  2106,  2115,  2117,
    2121,  2125,  2145,  2149,  2151,  2155,  2156,  2159,  2161,  2163,
    2165,  2167,  2170,  2173,  2177,  2183,  2187,  2191,  2193,  2198,
    2199,  2203,  2207,  2209,  2213,  2215,  2217,  2222,  2226,  2228,
    2230,  2233,  2235,  2236,  2237,  2238,  2239,  2240,  2241,  2242,
    2245,  2246,  2252,  2255,  2256,  2258,  2262,  2263,  2266,  2267,
    2269,  2273,  2274,  2275,  2276,  2278,  2281,  2282,  2291,  2293,
    2300,  2307,  2314,  2323,  2325,  2327,  2331,  2333,  2337,  2346,
    2353,  2360,  2362,  2366,  2370,  2376,  2378,  2383,  2387,  2391,
    2398,  2405,  2415,  2417,  2421,  2433,  2436,  2445,  2458,  2464,
    2470,  2476,  2484,  2494,  2496,  2500,  2521,  2546,  2548,  2552,
    2584,  2585,  2589,  2589,  2594,  2598,  2606,  2615,  2624,  2634,
    2640,  2643,  2645,  2649,  2657,  2672,  2679,  2681,  2685,  2701,
    2701,  2705,  2707,  2719,  2721,  2725,  2731,  2743,  2755,  2772,
    2801,  2802,  2810,  2811,  2815,  2817,  2819,  2830,  2834,  2840,
    2842,  2846,  2848,  2850,  2854,  2856,  2860,  2862,  2864,  2866,
    2868,  2870,  2872,  2874,  2876,  2878,  2880,  2882,  2884,  2886,
    2888,  2890,  2892,  2894,  2896,  2898,  2900,  2902,  2904,  2908,
    2909,  2920,  2994,  3006,  3008,  3012,  3143,  3193,  3237,  3279,
    3337,  3339,  3341,  3380,  3423,  3434,  3435,  3439,  3444,  3445,
    3449,  3451,  3457,  3459,  3465,  3475,  3481,  3488,  3494,  3502,
    3510,  3526,  3536,  3549,  3556,  3558,  3581,  3583,  3585,  3587,
    3589,  3591,  3593,  3595,  3599,  3599,  3599,  3613,  3615,  3638,
    3640,  3642,  3658,  3660,  3662,  3676,  3679,  3681,  3689,  3691,
    3693,  3695,  3749,  3769,  3784,  3793,  3796,  3846,  3852,  3857,
    3875,  3877,  3879,  3881,  3883,  3886,  3892,  3894,  3896,  3899,
    3901,  3903,  3930,  3939,  3948,  3949,  3951,  3956,  3963,  3971,
    3973,  3977,  3980,  3982,  3986,  3992,  3994,  3996,  3998,  4002,
    4004,  4013,  4014,  4021,  4022,  4026,  4030,  4051,  4054,  4058,
    4060,  4067,  4072,  4073,  4084,  4101,  4124,  4149,  4150,  4157,
    4159,  4161,  4163,  4165,  4169,  4245,  4257,  4264,  4266,  4267,
    4269,  4278,  4285,  4292,  4300,  4305,  4310,  4313,  4316,  4319,
    4322,  4325,  4329,  4347,  4352,  4371,  4390,  4394,  4395,  4398,
    4402,  4407,  4414,  4416,  4418,  4422,  4423,  4434,  4449,  4453,
    4460,  4463,  4473,  4486,  4499,  4503,  4506,  4509,  4513,  4522,
    4525,  4529,  4531,  4537,  4541,  4543,  4545,  4552,  4556,  4558,
    4560,  4564,  4583,  4599,  4608,  4617,  4619,  4623,  4649,  4664,
    4679,  4696,  4704,  4713,  4721,  4726,  4731,  4753,  4769,  4771,
    4775,  4777,  4784,  4786,  4788,  4792,  4794,  4796,  4798,  4800,
    4802,  4806,  4809,  4812,  4818,  4824,  4833,  4837,  4844,  4846,
    4850,  4852,  4854,  4859,  4864,  4869,  4874,  4883,  4888,  4894,
    4895,  4910,  4911,  4912,  4913,  4914,  4915,  4916,  4917,  4918,
    4919,  4920,  4921,  4922,  4923,  4924,  4925,  4926,  4927,  4928,
    4931,  4932,  4933,  4934,  4935,  4936,  4937,  4938,  4939,  4940,
    4941,  4942,  4943,  4944,  4945,  4946,  4947,  4948,  4949,  4950,
    4951,  4952,  4953,  4954,  4955,  4956,  4957,  4958,  4959,  4960,
    4961,  4962,  4963,  4964,  4965,  4966,  4967,  4971,  4974,  4983,
    4994,  5014,  5018,  5020,  5024,  5037,  5041,  5043,  5047,  5058,
    5069,  5073,  5075,  5079,  5081,  5091,  5103,  5123,  5143,  5165,
    5171,  5180,  5188,  5194,  5202,  5209,  5215,  5224,  5228,  5234,
    5242,  5256,  5270,  5275,  5291,  5306,  5334,  5336,  5340,  5342,
    5346,  5375,  5398,  5419,  5420,  5424,  5445,  5447,  5451,  5459,
    5463,  5468,  5470,  5472,  5474,  5480,  5482,  5486,  5496,  5500,
    5502,  5507,  5511,  5515,  5521,  5531,  5533,  5537,  5539,  5541,
    5548,  5566,  5567,  5571,  5573,  5577,  5584,  5594,  5623,  5638,
    5645,  5663,  5665,  5669,  5683,  5709,  5722,  5738,  5740,  5743,
    5745,  5751,  5755,  5783,  5785,  5789,  5797,  5803,  5806,  5857,
    5916,  5918,  5921,  5925,  5929,  5933,  5950,  5962,  5966,  5970,
    5980,  5985,  5992,  6001,  6001,  6012,  6023,  6025,  6029,  6040,
    6044,  6046,  6050,  6061,  6065,  6067,  6071,  6083,  6085,  6092,
    6094,  6098,  6114,  6122,  6133,  6135,  6139,  6142,  6145,  6150,
    6160,  6162,  6166,  6168,  6177,  6178,  6182,  6184,  6189,  6190,
    6191,  6192,  6193,  6194,  6195,  6196,  6197,  6198,  6201,  6206,
    6210,  6214,  6218,  6231,  6235,  6239,  6243,  6246,  6248,  6250,
    6254,  6256,  6260,  6265,  6269,  6273,  6275,  6279,  6287,  6293,
    6300,  6303,  6305,  6309,  6311,  6315,  6327,  6329,  6333,  6337,
    6339,  6343,  6345,  6347,  6349,  6351,  6353,  6355,  6359,  6363,
    6367,  6371,  6375,  6382,  6388,  6393,  6396,  6399,  6412,  6414,
    6418,  6420,  6425,  6431,  6437,  6443,  6449,  6455,  6461,  6467,
    6473,  6482,  6488,  6505,  6507,  6515,  6523,  6525,  6529,  6533,
    6535,  6539,  6541,  6549,  6553,  6565,  6568,  6586,  6588,  6592,
    6594,  6598,  6600,  6604,  6608,  6612,  6621,  6625,  6629,  6634,
    6638,  6650,  6652,  6656,  6661,  6665,  6667,  6671,  6673,  6677,
    6682,  6689,  6712,  6714,  6716,  6718,  6720,  6724,  6735,  6739,
    6754,  6761,  6768,  6769,  6773,  6777,  6785,  6789,  6793,  6801,
    6806,  6820,  6822,  6826,  6828,  6837,  6839,  6841,  6843,  6879,
    6883,  6887,  6891,  6895,  6907,  6909,  6913,  6916,  6918,  6922,
    6927,  6934,  6937,  6945,  6949,  6954,  6956,  6963,  6967,  6971,
    6975,  6979,  6983,  6986,  6988,  6992,  6994,  6996,  7000,  7004,
    7016,  7018,  7022,  7024,  7028,  7031,  7034,  7038,  7044,  7056,
    7058,  7062,  7064,  7068,  7076,  7078,  7079,  7080,  7081,  7082,
    7083,  7084,  7085,  7086,  7087,  7088,  7089,  7090,  7091,  7092,
    7093,  7094,  7095,  7096,  7097,  7098,  7099,  7100,  7101,  7102,
    7103,  7106,  7112,  7118,  7124,  7130,  7134,  7140,  7141,  7142,
    7143,  7144,  7145,  7146,  7147,  7148,  7151,  7156,  7161,  7167,
    7173,  7179,  7184,  7190,  7196,  7202,  7209,  7215,  7221,  7228,
    7232,  7234,  7240,  7247,  7253,  7259,  7265,  7271,  7277,  7283,
    7289,  7295,  7301,  7307,  7313,  7323,  7328,  7334,  7338,  7344,
    7345,  7346,  7347,  7350,  7358,  7364,  7370,  7375,  7381,  7388,
    7394,  7398,  7404,  7405,  7406,  7407,  7408,  7409,  7412,  7421,
    7425,  7431,  7438,  7445,  7452,  7461,  7467,  7473,  7477,  7483,
    7484,  7487,  7493,  7499,  7503,  7510,  7511,  7514,  7520,  7526,
    7531,  7539,  7545,  7550,  7557,  7561,  7567,  7568,  7569,  7570,
    7571,  7572,  7573,  7574,  7575,  7576,  7577,  7581,  7586,  7591,
    7598,  7603,  7609,  7615,  7620,  7625,  7630,  7634,  7639,  7644,
    7648,  7653,  7657,  7663,  7668,  7674,  7679,  7685,  7695,  7699,
    7703,  7707,  7713,  7716,  7720,  7721,  7722,  7723,  7724,  7725,
    7728,  7732,  7736,  7738,  7740,  7744,  7746,  7748,  7752,  7754,
    7758,  7760,  7764,  7767,  7770,  7775,  7777,  7779,  7781,  7783,
    7787,  7791,  7796,  7800,  7802,  7806,  7808,  7812,  7816,  7820,
    7821,  7822,  7823,  7824,  7827,  7831,  7835,  7839,  7843,  7847,
    7849,  7853,  7854,  7857,  7861,  7865,  7867,  7871,  7872,  7873,
    7877,  7881,  7885,  7889,  7891,  7895,  7899
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
  "SPF_PARALLEL_REG", "SPF_END_PARALLEL_REG", "BINARY_OP", "UNARY_OP",
  "$accept", "program", "stat", "thislabel", "entry", "new_prog",
  "proc_attr", "procname", "funcname", "typedfunc", "opt_result_clause",
  "name", "progname", "blokname", "arglist", "args", "arg", "filename",
  "needkeyword", "keywordoff", "keyword_if_colon_follow", "spec",
  "interface", "defined_op", "operator", "intrinsic_op", "type_dcl",
  "end_type", "dcl", "options", "attr_spec_list", "attr_spec",
  "intent_spec", "access_spec", "intent", "optional", "static", "private",
  "private_attr", "sequence", "public", "public_attr", "type",
  "opt_key_hedr", "attrib", "att_type", "typespec", "typename", "lengspec",
  "proper_lengspec", "selector", "clause", "end_ioctl", "initial_value",
  "dimension", "allocatable", "pointer", "target", "common", "namelist",
  "namelist_group", "comblock", "var", "external", "intrinsic",
  "equivalence", "equivset", "equivlist", "equi_object", "data", "data1",
  "data_in", "in_data", "datapair", "datalvals", "datarvals", "datalval",
  "data_null", "d_name", "dataname", "datasubs", "datarange",
  "iconexprlist", "opticonexpr", "dataimplieddo", "dlist", "dataelt",
  "datarval", "datavalue", "BOZ_const", "int_const", "unsignedint",
  "real_const", "unsignedreal", "complex_const_data", "complex_part",
  "iconexpr", "iconterm", "iconfactor", "iconprimary", "savelist",
  "saveitem", "use_name_list", "use_key_word", "no_use_key_word",
  "use_name", "paramlist", "paramitem", "module_proc_stmt",
  "proc_name_list", "use_stat", "module_name", "only_list", "only_name",
  "rename_list", "rename_name", "dims", "dimlist", "@1", "dim", "ubound",
  "labellist", "label", "implicit", "implist", "impitem", "imptype", "@2",
  "type_implicit", "letgroups", "letgroup", "letter", "inside", "in_dcl",
  "opt_double_colon", "funarglist", "funarg", "funargs", "subscript_list",
  "expr", "uexpr", "addop", "ident", "lhs", "array_ele_substring_func_ref",
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
  "target_subscript", "aster_expr", "omp_specification_directive",
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
       0,   327,   328,     1,     2,     3,     4,     5,     6,     7,
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
     318,   319,   320,   321,   322,   323,   324,   325,   326,   329,
     330
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   331,   332,   332,   333,   333,   333,   333,   333,   333,
     333,   334,   335,   335,   335,   335,   335,   335,   335,   335,
     336,   337,   337,   337,   338,   339,   340,   340,   340,   340,
     341,   341,   342,   343,   343,   344,   344,   345,   345,   345,
     346,   346,   347,   347,   348,   349,   350,   351,   352,   352,
     352,   352,   352,   352,   352,   352,   352,   352,   352,   352,
     352,   352,   352,   352,   352,   352,   352,   352,   352,   352,
     352,   352,   352,   352,   352,   352,   352,   353,   353,   353,
     353,   353,   354,   355,   355,   356,   356,   356,   356,   356,
     356,   356,   356,   356,   356,   356,   356,   356,   356,   356,
     356,   356,   356,   357,   357,   358,   358,   359,   359,   360,
     360,   360,   361,   361,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   363,   363,   363,   364,
     364,   365,   365,   366,   366,   367,   367,   368,   368,   369,
     370,   371,   371,   372,   373,   373,   374,   375,   375,   376,
     376,   377,   378,   378,   378,   378,   378,   378,   378,   379,
     379,   380,   380,   380,   381,   381,   381,   381,   382,   382,
     382,   382,   383,   384,   384,   384,   385,   385,   386,   386,
     387,   387,   388,   388,   389,   389,   389,   389,   390,   390,
     390,   391,   392,   392,   393,   394,   394,   395,   395,   396,
     396,   397,   398,   398,   399,   399,   399,   400,   401,   401,
     402,   403,   404,   405,   405,   406,   406,   407,   407,   407,
     407,   407,   408,   409,   410,   411,   412,   413,   413,   414,
     414,   415,   416,   416,   417,   417,   417,   417,   418,   418,
     418,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   420,   421,   421,   421,   422,   422,   423,   423,
     423,   424,   424,   424,   424,   425,   426,   426,   427,   427,
     427,   427,   427,   428,   428,   428,   429,   429,   430,   430,
     430,   431,   431,   432,   432,   433,   433,   434,   435,   436,
     436,   436,   437,   437,   438,   439,   440,   440,   441,   441,
     441,   441,   442,   443,   443,   444,   444,   445,   445,   446,
     447,   447,   449,   448,   448,   450,   450,   450,   450,   451,
     451,   452,   452,   453,   454,   454,   455,   455,   456,   458,
     457,   459,   459,   460,   460,   461,   461,   462,   463,   464,
     465,   465,   466,   466,   467,   467,   467,   468,   468,   469,
     469,   470,   470,   470,   471,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   472,
     472,   473,   474,   474,   474,   475,   475,   475,   475,   476,
     477,   477,   477,   477,   478,   479,   479,   480,   481,   481,
     482,   482,   482,   482,   482,   483,   483,   483,   483,   484,
     485,   485,   485,   486,   487,   487,   488,   488,   488,   488,
     488,   488,   488,   488,   490,   491,   489,   492,   492,   493,
     493,   493,   494,   494,   494,   495,   496,   496,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   498,   498,   499,   499,   499,   500,   500,   501,
     501,   501,   501,   501,   502,   503,   503,   503,   503,   504,
     504,   505,   505,   506,   506,   507,   508,   509,   510,   511,
     511,   512,   513,   513,   514,   515,   515,   516,   516,   517,
     517,   517,   517,   517,   518,   518,   518,   518,   518,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   518,   518,
     518,   518,   519,   520,   520,   520,   520,   521,   521,   522,
     523,   523,   524,   524,   524,   525,   525,   526,   527,   528,
     529,   529,   529,   529,   529,   529,   529,   529,   529,   529,
     529,   529,   529,   530,   531,   531,   531,   532,   533,   533,
     533,   534,   534,   535,   535,   536,   536,   537,   537,   537,
     537,   537,   537,   538,   539,   540,   541,   541,   542,   542,
     543,   543,   544,   544,   544,   545,   545,   545,   545,   545,
     545,   546,   546,   546,   546,   546,   547,   548,   549,   549,
     550,   550,   550,   550,   550,   550,   550,   550,   550,   551,
     551,   552,   552,   552,   552,   552,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   552,   552,   552,   552,
     553,   553,   553,   553,   553,   553,   553,   553,   553,   553,
     553,   553,   553,   553,   553,   553,   553,   553,   553,   553,
     553,   553,   553,   553,   553,   553,   553,   553,   553,   553,
     553,   553,   553,   553,   553,   553,   553,   554,   554,   554,
     555,   556,   557,   557,   558,   559,   560,   560,   561,   562,
     563,   564,   564,   565,   565,   566,   567,   567,   567,   568,
     568,   569,   570,   570,   571,   572,   572,   573,   574,   574,
     575,   576,   576,   577,   578,   578,   579,   579,   580,   580,
     581,   582,   583,   584,   584,   585,   586,   586,   587,   588,
     588,   588,   588,   588,   588,   588,   588,   589,   590,   591,
     591,   592,   593,   593,   594,   595,   595,   596,   596,   596,
     597,   598,   598,   599,   599,   600,   601,   601,   602,   603,
     603,   604,   604,   605,   606,   607,   608,   609,   609,   610,
     610,   610,   611,   612,   612,   613,   613,   613,   614,   614,
     615,   615,   616,   616,   616,   616,   616,   616,   616,   616,
     616,   616,   617,   619,   618,   618,   620,   620,   621,   622,
     623,   623,   624,   625,   626,   626,   627,   628,   628,   629,
     629,   630,   631,   632,   633,   633,   634,   635,   635,   636,
     637,   637,   638,   638,   639,   639,   640,   640,   641,   641,
     641,   641,   641,   641,   641,   641,   641,   641,   642,   642,
     643,   643,   644,   645,   645,   646,   647,   648,   648,   648,
     649,   649,   650,   650,   651,   652,   652,   653,   654,   654,
     654,   655,   655,   656,   656,   656,   657,   657,   658,   659,
     659,   660,   660,   660,   660,   660,   660,   660,   661,   662,
     663,   664,   665,   665,   665,   666,   667,   668,   669,   669,
     670,   670,   671,   671,   671,   671,   671,   671,   671,   671,
     671,   672,   672,   673,   673,   673,   673,   673,   674,   675,
     675,   676,   676,   676,   676,   677,   678,   679,   679,   680,
     680,   681,   681,   682,   683,   684,   685,   686,   687,   687,
     688,   689,   689,   690,   690,   691,   691,   692,   692,   693,
     693,   694,   695,   695,   695,   695,   695,   696,   697,   698,
     698,   699,   700,   700,   701,   702,   702,   703,   704,   705,
     705,   706,   706,   707,   707,   708,   708,   708,   708,   709,
     710,   711,   712,   713,   714,   714,   715,   716,   716,   717,
     717,   718,   719,   720,   721,   722,   722,   723,   724,   725,
     726,   727,   728,   729,   729,   730,   730,   730,   731,   732,
     733,   733,   734,   734,   735,   735,   736,   737,   737,   738,
     738,   739,   739,   740,   741,   742,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   743,   744,   745,   745,   746,   746,   747,   747,   747,
     747,   747,   747,   747,   747,   747,   748,   749,   750,   751,
     752,   753,   754,   755,   755,   755,   756,   757,   758,   759,
     760,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   762,   762,   763,   763,   764,
     764,   764,   764,   765,   765,   766,   767,   767,   768,   768,
     769,   769,   770,   770,   770,   770,   770,   770,   771,   772,
     772,   773,   773,   773,   773,   774,   774,   775,   775,   776,
     776,   777,   777,   778,   778,   779,   779,   780,   781,   782,
     783,   783,   784,   784,   785,   785,   786,   786,   786,   786,
     786,   786,   786,   786,   786,   786,   786,   787,   788,   788,
     789,   790,   790,   791,   792,   793,   794,   795,   796,   797,
     798,   799,   799,   800,   800,   801,   801,   802,   803,   803,
     803,   803,   804,   805,   806,   806,   806,   806,   806,   806,
     807,   808,   809,   809,   809,   810,   810,   810,   811,   811,
     812,   812,   813,   813,   813,   814,   814,   814,   814,   814,
     815,   816,   817,   818,   818,   819,   819,   820,   821,   822,
     822,   822,   822,   822,   823,   824,   825,   826,   827,   828,
     828,   829,   829,   830,   831,   832,   832,   833,   833,   833,
     834,   835,   836,   837,   837,   838,   839
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
       1,     1,     1,     1,     1,     1,     1,     3,     8,     3,
       2,     3,     1,     3,     1,     3,     1,     3,     1,     4,
       3,     1,     3,     1,     3,     1,     4,     4,     4,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     0,     5,     6,     8,     1,     3,     1,     1,
       1,     4,     1,     0,     2,     3,     2,     4,     0,     1,
       5,     4,     6,     4,     1,     4,     4,     1,     6,     1,
       3,     1,     1,     4,     1,     1,     3,     1,     1,     3,
       1,     0,     1,     2,     3,     1,     2,     5,     4,     4,
       6,     1,     3,     1,     1,     6,     4,     1,     3,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     6,     4,
       1,     4,     1,     1,     1,     1,     4,     2,     7,     1,
       4,     1,    11,     0,     2,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     8,     1,
       3,     2,     2,     7,     1,     3,     1,     3,     1,     4,
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
       4,     2,     1,     3,     3,     0,     1,     2,     2,     2,
       2,     9,     5,     1,     3,     2,     2,     2,     9,     4,
       1,     3,     1,     1,     2,     0,     7,     1,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
     149,   779,   339,   537,   537,   537,   537,   537,   339,   537,
     554,   537,    20,   537,   537,   158,   537,   560,   339,   154,
     537,   339,   537,   537,   339,   485,   537,   537,   537,   338,
     537,   339,   537,   537,   340,   781,   537,   155,   156,   775,
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
       0,   339,     8,   339,   537,   537,   537,   773,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   339,   537,   774,   537,  1197,   537,
    1198,   537,   537,   537,     0,     0,     0,     0,  1208,   609,
       0,    37,   609,    73,    48,    49,    50,    65,    66,    76,
      68,    69,    67,   109,    58,     0,   146,   151,    52,    70,
      71,    72,    51,    59,    54,    55,    56,    60,   207,    75,
      74,    57,   609,   445,   440,   453,     0,     0,     0,   456,
     439,   438,     0,   508,   511,   537,   509,     0,   537,     0,
     537,     0,     0,   551,    53,   459,   611,   614,   620,   616,
     615,   621,   622,   623,   624,   613,   630,   612,   631,   617,
       0,   770,   618,   625,   627,   626,   657,   632,   634,   635,
     633,   636,   637,   638,   639,   640,   619,   641,   642,   644,
     645,   643,   647,   648,   646,   665,   658,   659,   660,   661,
     649,   650,   651,   652,   653,   654,   655,   656,   662,   663,
     664,   629,   666,   628,  1006,  1005,  1007,  1008,  1009,  1010,
    1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,
    1021,  1004,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,   460,  1164,  1166,  1168,  1169,  1165,  1167,   461,  1199,
    1200,  1201,  1202,  1203,     0,     0,   340,     0,     0,     0,
       0,     0,     0,     0,   980,    35,     0,     0,   596,     0,
       0,     0,     0,     0,     0,   454,   507,   481,   210,     0,
       0,     0,   481,     0,   312,   339,   718,     0,   718,   538,
       0,    23,   481,     0,   481,   961,     0,   977,   483,   481,
     481,   481,    32,   484,    81,   444,   944,   481,   938,   105,
     481,    37,   481,     0,   340,     0,     0,    63,     0,     0,
     329,    44,     7,   955,     0,     0,     0,     0,     0,    77,
     340,     0,   975,   522,     0,     0,     0,   296,   295,     0,
       0,   802,     0,     0,   340,     0,     0,   538,     0,   340,
       0,     0,     0,   340,    33,   340,    22,   597,     0,    21,
       0,     0,     0,     0,     0,     0,     0,   398,   340,    45,
     140,     0,     0,     0,     0,     0,     0,     0,     0,   777,
     340,     0,   340,     0,     0,   978,   979,     0,   339,   340,
       0,     0,     0,   597,     0,  1150,  1149,  1154,  1031,   718,
    1156,   718,  1146,  1148,  1032,  1137,  1140,  1143,   718,   718,
     718,  1152,  1145,  1147,   718,   718,   718,   718,  1085,   718,
     718,  1162,  1119,     0,    45,  1171,  1174,  1177,     0,    45,
      45,    45,  1226,  1207,   610,     4,    20,    20,     0,     0,
      45,     5,     0,     0,     0,     0,     0,    45,    20,     0,
       0,     0,   147,   164,     0,     0,     0,     0,   528,     0,
     528,     0,     0,     0,     0,   528,   222,     6,   486,   537,
     537,   446,   441,     0,   457,   448,   447,   455,    82,   172,
       0,     0,     0,   406,     0,   405,   410,   408,   409,   407,
     381,     0,     0,   351,   382,   354,   384,   383,   355,   400,
     402,   395,   353,   356,   596,   398,   542,   543,     0,   380,
     379,    32,     0,   600,   601,   540,     0,   598,   597,     0,
     544,   597,   562,   546,   545,   598,   549,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,   766,   767,
     765,     0,   763,   753,     0,     0,   435,     0,   323,     0,
     524,   963,   964,   960,    45,   310,   797,   799,   962,    36,
      13,   596,     0,   481,     0,   192,     0,   310,     0,   184,
       0,   700,   698,   832,   916,   917,   796,   793,   794,   482,
     516,   222,   435,    45,   310,   667,   972,   967,   470,   341,
       0,     0,     0,     0,     0,   710,   713,   702,     0,   497,
     674,   671,   672,   451,     0,     0,   500,   973,   442,   443,
     458,   452,   471,   106,   499,    45,   517,     0,   199,     0,
     382,     0,     0,    37,    25,   792,   789,   790,   324,   326,
       0,     0,    45,   956,   957,     0,   691,   689,   678,   675,
     676,     0,     0,    78,     0,    45,   976,   974,     0,     0,
     937,     0,    45,     0,    19,     0,     0,     0,     0,   942,
       0,     0,     0,   497,   523,     0,     0,   920,   947,   597,
       0,   597,   598,   139,    34,    12,   143,   574,     0,   754,
       0,     0,     0,   718,   697,   695,   877,   914,   915,     0,
     694,   692,   948,   399,   514,     0,     0,     0,   898,     0,
     910,   909,   912,   911,   683,     0,   681,   685,     0,     0,
      37,    24,     0,   310,   929,   932,     0,    45,     0,   302,
     298,     0,     0,   575,   310,     0,   527,     0,  1089,  1084,
     527,  1121,  1151,     0,   527,   527,   527,   527,   527,   527,
    1144,   310,    46,  1170,  1179,  1180,     0,     0,    45,     0,
       0,  1209,  1211,  1212,     0,     0,  1215,  1217,  1218,  1219,
       0,     0,  1223,     0,     0,    20,    43,    38,    42,     0,
      40,    17,    46,   310,   132,   134,   136,   110,     0,     0,
      20,   339,   148,   538,   596,   165,   146,   310,   179,   181,
     183,   187,   527,   190,   527,   196,   198,   200,   209,     0,
     213,     0,    45,     0,   449,   424,     0,   351,   364,   363,
     376,   362,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   596,     0,     0,   596,     0,     0,   398,   404,   396,
     512,     0,     0,   515,   568,   569,   573,     0,   565,     0,
     567,     0,   606,     0,     0,     0,     0,     0,   553,   567,
     557,     0,     0,   580,   547,   578,     0,     0,   351,   353,
     550,   584,   583,   552,   669,   310,   690,   693,   696,   699,
     310,   339,     0,   930,     0,    45,   748,   178,     0,     0,
       0,     0,     0,     0,   312,   801,     0,   529,     0,   475,
     479,     0,   469,   596,     0,   194,   185,     0,   321,     0,
     208,     0,     0,   670,   596,     0,   776,   319,   316,   313,
     315,   320,   310,   718,   715,   724,   719,     0,     0,     0,
       0,     0,   716,   702,   718,     0,   780,     0,   498,   539,
       0,     0,     0,    18,   204,     0,     0,     0,   206,   195,
       0,   494,   492,   489,     0,    45,     0,   329,     0,     0,
     332,   330,     0,    45,   958,   381,   906,   953,     0,     0,
     951,     0,     0,    87,    88,    86,    85,    91,    90,   102,
      95,    98,    97,   100,    99,    96,   101,    94,    92,    89,
      93,    83,     0,    84,   197,     0,     0,     0,     0,     0,
       0,   297,     0,   188,   436,     0,    45,   943,   941,   133,
     806,     0,   804,     0,     0,   292,   539,   180,     0,   577,
       0,   576,   287,   287,     0,   749,     0,   718,   702,   924,
       0,     0,   921,   284,   283,    62,   281,     0,     0,     0,
       0,     0,     0,   680,   679,   135,    14,   182,   931,    45,
     934,   933,   146,     0,   103,    47,     0,     0,   686,     0,
     718,   527,     0,  1118,  1088,  1083,   718,   527,  1120,  1163,
     718,   527,   718,   527,   527,   527,   718,   527,   718,   527,
     687,     0,     0,     0,     0,  1191,     0,     0,  1178,  1182,
    1184,  1183,    45,  1173,   840,  1192,     0,  1176,     0,     0,
       0,   983,     0,     0,    45,  1204,     0,     0,     0,    45,
    1205,  1225,    45,  1206,    28,    37,     0,     0,    39,     0,
      30,   159,   116,   310,   339,   118,   120,     0,   121,   114,
     122,   130,   129,   123,   124,   125,     0,   112,   115,    26,
       0,   310,     0,     0,   144,   177,     0,     0,   222,   222,
       0,   224,   217,   221,     0,     0,     0,   352,     0,   359,
     361,   358,   357,   375,   377,   371,   365,   504,   368,   366,
     369,   367,   370,   372,   374,   360,   373,   378,   596,   411,
     389,     0,   343,     0,   414,   415,   401,   412,   403,     0,
     596,   513,     0,   532,   530,     0,   596,   564,   571,   572,
     570,   599,   608,   603,   605,   607,   604,   602,   563,   548,
       0,     0,     0,   351,     0,     0,     0,     0,     0,   688,
     769,     0,   779,   772,     0,   781,   775,     0,   773,   774,
     771,   764,     0,   390,   391,   429,     0,     0,   506,     0,
       0,   349,     0,     0,   800,   477,   476,     0,   474,     0,
     193,     0,   527,   795,   427,   428,   432,     0,     0,     0,
       0,   314,   317,   176,     0,   596,     0,     0,     0,     0,
       0,   703,   714,   310,   462,   718,   673,     0,   481,     0,
       0,   201,     0,   394,   966,     0,     0,     0,    16,   791,
     327,   337,     0,   333,   335,   331,     0,     0,     0,     0,
       0,     0,     0,   950,   677,    80,    79,   128,   126,   127,
     340,     0,   487,   423,     0,     0,     0,     0,   191,     0,
     520,     0,     0,   718,     0,     0,    64,   527,   505,   599,
     138,     0,   142,    45,     0,   702,     0,     0,     0,     0,
     919,     0,     0,     0,     0,     0,   899,   901,   684,   682,
       0,    45,   936,    45,   935,   145,   340,     0,   502,     0,
    1153,     0,   718,  1155,     0,   718,     0,     0,   718,     0,
     718,     0,   718,     0,   718,     0,     0,     0,    45,     0,
       0,     0,  1181,     0,  1172,  1175,   987,   985,   986,    45,
     982,     0,    45,  1210,     0,     0,     0,  1216,  1224,    15,
      29,    41,     0,   173,   160,   117,     0,    45,     0,    45,
      27,   159,   539,   539,   169,   172,   168,     0,   186,   189,
     214,     0,     0,     0,   247,   245,   252,   249,   263,   256,
     261,     0,     0,   215,   238,   250,   242,   253,   243,   258,
     244,     0,   237,     0,   232,   229,   218,   219,     0,     0,
     425,   351,     0,   387,   596,   347,   344,   345,     0,   398,
       0,   534,   533,     0,     0,   579,   352,     0,     0,     0,
     351,   586,   351,   590,   351,   588,   310,     0,   596,   596,
     596,   518,     0,     0,     0,   965,     0,   311,   478,   480,
     172,   322,     0,   596,   519,     0,     0,   969,   596,   968,
     318,   320,   717,     0,     0,     0,   727,     0,     0,     0,
       0,   701,   464,   481,   501,     0,   203,   202,   381,   493,
     490,   488,     0,   491,     0,   328,     0,     0,     0,     0,
       0,     0,   952,     0,   997,     0,     0,   422,   417,   939,
     940,   712,   310,   946,   437,   805,   808,   814,   294,   293,
       0,   287,     0,     0,   289,   288,     0,   750,   751,   704,
       0,   928,   927,     0,   925,     0,   922,   282,     0,  1003,
     992,     0,   990,   993,   745,     0,     0,   913,   905,     0,
       0,     0,     0,     0,   300,     0,   299,   307,     0,  1162,
       0,  1162,  1162,  1098,     0,  1092,  1094,  1095,  1093,   718,
    1097,  1096,     0,  1162,   718,  1116,  1115,     0,     0,  1159,
    1158,     0,     0,  1162,     0,  1162,     0,   718,  1037,  1041,
    1042,  1043,  1039,  1040,  1044,  1045,  1038,     0,  1126,  1130,
    1131,  1132,  1128,  1129,  1133,  1134,  1127,  1136,  1135,   718,
       0,  1079,  1081,  1082,  1080,   718,     0,  1109,  1110,   718,
       0,     0,     0,     0,     0,     0,  1193,     0,     0,   841,
     984,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   783,     0,   111,     0,   173,     0,   146,     0,   171,
     170,   267,   253,   266,     0,   255,   260,   254,   259,     0,
       0,     0,     0,     0,   222,   212,   223,   241,     0,   222,
     234,   235,     0,     0,     0,     0,   278,   223,   279,     0,
       0,   227,   268,   273,   276,   229,   220,     0,   503,     0,
     413,   385,   388,     0,   346,     0,   531,   566,   567,     0,
       0,   351,     0,     0,     0,   768,   762,   778,     0,   596,
       0,     0,     0,   525,   350,     0,   340,   526,     0,     0,
     971,     0,     0,     0,   731,     0,   729,   726,   721,   725,
     723,     0,    45,     0,   463,   450,   205,   334,   336,     0,
       0,     0,   954,   949,   131,     0,   996,   421,     0,     0,
     416,   945,     0,    45,   803,   815,   816,   821,   825,   818,
     826,   827,   822,   824,   823,   819,   820,     0,     0,     0,
       0,   285,     0,     0,     0,     0,   923,   918,   472,     0,
     989,   718,   900,     0,     0,   875,   104,   306,   301,   303,
       0,     0,     0,  1047,   718,  1048,  1049,    45,  1090,   718,
    1117,  1113,   718,  1162,     0,  1046,    45,  1050,     0,  1051,
       0,  1035,   718,  1124,   718,  1077,   718,  1107,   718,  1185,
    1186,  1187,  1195,  1196,    45,  1190,  1188,  1189,  1214,   887,
     888,   889,   886,   891,   885,   892,   884,   883,   882,   890,
     878,     0,     0,    45,  1213,  1221,  1222,  1220,    31,   175,
     174,     0,     0,   119,   113,   107,     0,     0,   161,   596,
     166,     0,   248,   246,   264,   257,   262,   216,   222,   596,
       0,   240,   236,   223,     0,   233,     0,   270,   269,     0,
     225,   229,     0,     0,     0,     0,     0,   230,     0,   426,
     386,   348,   397,     0,   581,   593,   595,   594,     0,     0,
     393,   430,     0,     0,   798,     0,   433,     0,   668,   970,
     746,   720,     0,    45,     0,     0,     0,   833,   959,   834,
    1002,     0,   999,  1001,   420,   419,     0,     0,   807,     0,
     817,     0,   288,     0,     0,   755,   752,   710,   705,   706,
     708,   709,   926,   991,   995,     0,     0,   381,     0,     0,
       0,     0,     0,   309,   308,   521,     0,     0,     0,  1091,
    1114,     0,  1161,  1160,     0,     0,     0,  1036,  1125,  1078,
    1108,  1194,     0,     0,     0,     0,     0,   784,   162,   163,
       0,     0,   239,   596,   241,     0,   280,   228,     0,   272,
     271,   274,   275,   277,   473,     0,   760,   759,   761,     0,
     757,   392,   431,     0,   981,   434,     0,   730,     0,   722,
       0,     0,     0,   998,   418,     0,     0,     0,     0,     0,
     896,     0,     0,     0,     0,     0,     0,   286,   291,   290,
       0,     0,     0,   988,   902,   903,     0,   831,   876,   876,
     305,   304,  1063,  1062,  1061,  1068,  1069,  1070,  1067,  1064,
    1066,  1065,  1074,  1071,  1072,  1073,     0,  1058,  1102,  1101,
    1103,  1104,     0,  1163,  1053,  1055,  1054,     0,  1057,  1056,
       0,     0,   879,   785,     0,   172,   265,     0,     0,   227,
     226,     0,     0,   756,   510,     0,     0,     0,   466,  1000,
     813,   812,     0,   810,   718,   845,     0,     0,     0,     0,
       0,   894,   895,     0,     0,     0,     0,   707,   907,   994,
      45,     0,     0,     0,     0,     0,  1100,  1157,  1052,   880,
       0,     0,     0,   251,   231,   495,   758,   747,   734,   728,
     732,     0,     0,   809,   850,   846,     0,     0,     0,     0,
       0,     0,     0,     0,   837,     0,   467,   711,     0,     0,
     830,    45,    45,   873,  1060,  1059,     0,     0,   354,   788,
     782,   786,   167,     0,     0,   465,   811,     0,     0,     0,
       0,   843,   835,     0,   829,     0,   893,   844,     0,   836,
       0,   908,     0,     0,     0,  1099,   881,     0,   496,     0,
     737,     0,   735,   738,   848,   849,     0,   851,   853,     0,
       0,     0,   838,   468,   904,   874,   872,   787,   740,   741,
       0,   733,     0,   847,     0,   842,   828,     0,     0,     0,
     739,   742,   736,   852,     0,     0,   856,   897,   839,   743,
       0,     0,     0,   854,   744,   858,   857,    45,     0,     0,
     859,   864,   866,   867,     0,     0,     0,    45,   855,    45,
      45,   596,   870,   869,   868,   860,     0,   862,   863,     0,
     865,     0,    45,   871,   861
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   199,   365,   200,   810,   723,   201,
     871,   590,   775,   660,   540,   869,   870,   422,   872,  1188,
    1457,   202,   203,   591,  1092,  1093,   204,   205,   206,   550,
    1236,  1237,  1096,  1238,   207,   208,   209,   210,  1122,   211,
     212,  1123,   213,   553,   214,   215,   216,   217,  1503,  1504,
     886,  1515,   905,  1770,   218,   219,   220,   221,   222,   223,
     756,  1133,  1134,   224,   225,   226,   718,  1045,  1046,   227,
     228,   681,   433,   898,   899,  1531,   900,   901,  1808,  1541,
    1546,  1547,  1809,  1810,  1542,  1543,  1544,  1533,  1534,  1535,
    1536,  1782,  1538,  1539,  1540,  1784,  2017,  1812,  1813,  1814,
    1135,  1136,  1430,  1431,  1901,  1655,  1114,  1115,   229,   438,
     230,   820,  1918,  1919,  1686,  1687,   995,   690,   691,  1019,
    1020,  1007,  1008,   231,   728,   729,   730,   731,  1061,  1392,
    1393,  1394,   378,   355,   385,  1281,  1555,  1282,  1340,   967,
     593,   612,   594,   595,   596,   597,  1335,  1048,   938,  1822,
     794,   598,   599,   600,   601,   602,  1286,  1557,   603,  1256,
    1819,  1356,  1336,  1357,   988,  1105,   232,   233,  1864,   234,
     235,   663,  1000,  1001,   680,   404,   236,   237,   238,   239,
    1052,  1053,  1386,  1829,  1830,  1039,   240,   241,   242,   243,
    1170,   244,   941,  1294,   245,   357,   699,  1375,   246,   247,
     248,   249,   250,   623,   615,   947,   948,   949,   251,   252,
     253,   964,   965,   970,   971,   972,  1283,   777,   616,   772,
     535,   254,   255,   256,   685,   257,   701,   702,   258,   739,
     740,   259,   479,   805,   806,   808,   260,   261,   737,   262,
     791,   263,   785,   264,   672,  1036,   265,   266,  2068,  2069,
    2070,  2071,  1642,  1033,   388,   693,   694,  1032,  1607,  1670,
    1855,  1856,  2259,  2260,  2321,  2322,  2339,  2350,  2351,  1675,
    1853,   267,   268,  1657,   644,   780,   781,  1837,  2129,  2130,
    1838,   641,   642,   269,   270,   271,   272,  1981,  1982,  2290,
    2291,   273,   726,   727,   274,   677,   678,   275,   656,   657,
     276,   277,  1111,  1112,  1647,  2058,  2222,  2223,  1884,  1885,
    1886,  1887,  1888,   674,  1889,  1890,  1891,  2275,  1195,  1892,
    1893,  1894,  2225,  2299,  2326,  2327,  2355,  2356,  2369,  2370,
    2371,  2372,  2373,  2382,  1895,  2080,  2242,   787,  1763,  1970,
    1971,  1972,  1896,   799,  1445,  1446,  1913,  1129,  2239,   278,
     279,   280,   281,   282,   283,   284,   285,   768,  1131,  1132,
    1663,  1664,   286,   814,   287,   751,   288,   752,   289,  1108,
     290,   291,   292,   293,   294,  1069,  1070,   295,   734,   296,
     297,   298,   652,   653,   299,   300,  1360,  1597,   687,   301,
     302,   747,   303,   304,   305,   306,   307,   308,  1200,  1201,
     309,  1139,  1671,  1672,  2163,   310,  1635,  2051,  2052,  1673,
     311,   312,   313,   314,   315,  1171,  1717,   832,  1695,  1696,
    1697,  1721,  1722,  1723,  2197,  1724,  1725,  1698,  2087,  2285,
    2186,   316,  1177,  1745,   317,   318,   319,   320,  1161,  1699,
    1700,  1701,  2192,   321,  1179,  1749,   322,  1167,  1704,  1705,
    1706,   323,   324,   325,  1173,  1739,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,  1710,  1711,   833,  1466,   341,   342,   343,   344,   345,
     843,   844,   845,  1189,  1190,  1191,  1196,  1755,  1756,   346,
     347,   348,   349,   350,   351,   352,   353,   850,   851,   852,
     853,   855,   856,   857,   858,   859,   861,   862,   533
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1939
static const yytype_int16 yypact[] =
{
   -1939,   114, -1939, -1939, -1939, -1939,    90,  4747, -1939, -1939,
   -1939,   162, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939,   234, -1939, -1939,   196,   170, -1939, -1939, -1939,   274,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939,   346,   346, -1939, -1939, -1939, -1939, -1939,   346,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
     275, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,   346, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939,   479, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
     580,   629, -1939, -1939, -1939, -1939, -1939,   274, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939,   274, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939,   673,   679,   712,   346, -1939,   459,
     924,   733,   459, -1939, -1939, -1939,   762,   778,   781,   817,
   -1939, -1939, -1939,   560,   831,   346, -1939, -1939,   847,   865,
     868,   884,   589,   145,   895,   925,   959, -1939,   147, -1939,
   -1939, -1939,   459, -1939, -1939, -1939,   814,   311,  1650,  1991,
   -1939, -1939,  2740, -1939,   980, -1939, -1939,  1259, -1939,   984,
   -1939,   974,   984,   998, -1939, -1939,  1013, -1939, -1939, -1939,
    1016,  1036,  1056,  1067,  1073, -1939, -1939, -1939, -1939,  1076,
     123, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939,  1081, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939,   168,   346,   825,  1098,  1100,   718,
     346,   346,    96,   346, -1939,   346,   346,  1106, -1939,   445,
    1123,   346,   346,   346,   346, -1939, -1939,   346, -1939,  1138,
     142,   949,   346,  1173, -1939, -1939, -1939,   346, -1939,  1196,
     346, -1939,   346,  1222,   172, -1939,   949, -1939,   346,   346,
     346,   346, -1939, -1939, -1939, -1939, -1939,   346, -1939,   346,
     346,   733,   346,  1252,   825,   346,  1255, -1939,   346,   346,
   -1939, -1939, -1939,  1247,  1265,   346,   346,  1273,  1275,   346,
     825,  1289,  2740, -1939,  1295,  1312,   346, -1939,  1288,   346,
    1236, -1939,  1319,   346,   825,  1326,  1331, -1939,   718,   825,
     346,   346,  1610,   140,   346,   177, -1939, -1939,   251, -1939,
     257,   346,   346,   346,  1340,   346,   346,  2740,   182, -1939,
   -1939,  1341,   346,   346,   346,   346,   346,  2740,   346, -1939,
     825,   346,   825,   346,   346, -1939, -1939,   346, -1939,   825,
     346,  1350,  1351, -1939,   346, -1939, -1939,  1353, -1939, -1939,
    1355, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939,  1356, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939,   346, -1939, -1939,  1362,  1365,  1369, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,  1189,   144,
   -1939, -1939,   346,   346,   346,   346,  1332, -1939, -1939,  1261,
     346,   346, -1939,   586,   346,   346,   346,   346,   346,   656,
     346,  1236,   346,   346,  1252, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939,  1156, -1939, -1939, -1939, -1939, -1939, -1939,
    2740,  2740,  2740, -1939,  2740, -1939, -1939, -1939, -1939, -1939,
   -1939,  2740,  2967, -1939,    81,  1394, -1939,  1383, -1939,  1153,
    1161,  1387, -1939, -1939,  1385,  2740, -1939, -1939,  1345, -1939,
   -1939,  1384,  2276,  1394, -1939, -1939,  1091,     6, -1939,  1345,
   -1939, -1939, -1939,  1404,   314,   108,  2785,  2785,   346,   346,
     346,   346,   346,   346,   346,  1408, -1939,   346, -1939, -1939,
   -1939,   419, -1939, -1939,  1402,   346, -1939,  2740, -1939,  1178,
     802, -1939,  1405, -1939, -1939,  1406,  1414, -1939, -1939, -1939,
   -1939, -1939,  2397,   346,  1412, -1939,   346,  1406,   346, -1939,
     718, -1939, -1939, -1939, -1939, -1939, -1939,  1421, -1939, -1939,
   -1939, -1939, -1939, -1939,  1406, -1939, -1939,  1416, -1939, -1939,
     465,  1229,   346,   697,    83, -1939,  1417,  1263,  2740,  1285,
   -1939,  1432, -1939, -1939,  2740,  2740, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939,   346, -1939,   346,
    1429,   524,   346,   733, -1939, -1939,  1439, -1939,  1440, -1939,
    1434,  1246, -1939,  1443, -1939,   346, -1939, -1939, -1939,  1444,
   -1939,  1427,  3046, -1939,   346, -1939,  5264, -1939,   346,  2740,
   -1939,  1441, -1939,   346, -1939,   346,   346,   346,  1394,   890,
     346,   346,   346,  1285, -1939,   346,   651, -1939, -1939, -1939,
    2276,  1091, -1939, -1939, -1939, -1939, -1939, -1939,   168, -1939,
    1402,  1447,  1417, -1939, -1939, -1939, -1939, -1939, -1939,   346,
   -1939, -1939, -1939,  5264, -1939,   445,  1393,   346, -1939,  1446,
   -1939, -1939, -1939, -1939,  3138,   701, -1939, -1939,   479,   346,
     733, -1939,   346,  1406, -1939,  1450,  1442, -1939,   346, -1939,
    1454,  2740,  2740, -1939,  1406,   346,   112,   346,  1177,  1177,
     199,  1177, -1939,  1451,   200,   276,   353,   399,   429,   457,
   -1939,  1406,   743, -1939,  1457, -1939,   165,   261, -1939,   380,
     715, -1939, -1939, -1939,    46,   750, -1939, -1939, -1939, -1939,
    1144,   764, -1939,   346,   346, -1939, -1939, -1939, -1939,   779,
   -1939, -1939,  1262,  1406, -1939, -1939, -1939, -1939,  2301,   346,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939,  1406, -1939, -1939,
   -1939, -1939,  1463, -1939,  1463, -1939, -1939, -1939, -1939,   562,
   -1939,   379, -1939,  1461, -1939, -1939,  3202,  1464,  1469,  1469,
    1904, -1939,  2740,  2740,  2740,  2740,  2740,  2740,  2740,  2740,
    2740,  2740,  2740,  2740,  2740,  2740,  2740,  2740,  2740,  2740,
    2740, -1939,  1415,  1352,  1462,   329,   460,  2740, -1939, -1939,
   -1939,   787,  1267, -1939, -1939, -1939, -1939,   797, -1939,  1377,
     821,  2740,  1473,  2276,  2276,  2276,  2276,  2276, -1939,   824,
   -1939,   314,   314,  1394,  1476, -1939,  2785,  5264,   131,   136,
   -1939,  1477,  1478, -1939, -1939,  1406, -1939, -1939, -1939, -1939,
    1406, -1939,   766, -1939,   168, -1939, -1939, -1939,   346,  3255,
     346,  1474,  2740,  1424, -1939, -1939,   346, -1939,  2740,  3338,
   -1939,   798, -1939, -1939,  1455, -1939, -1939,   799, -1939,   346,
   -1939,   346,  1428, -1939, -1939,  1229, -1939, -1939, -1939, -1939,
   -1939,  3547,  1406, -1939, -1939, -1939,  1481,  1482,  1483,  1484,
    1485,  1487, -1939,  1263, -1939,   346, -1939,  3578, -1939, -1939,
     346,  3615,  3650, -1939,  1488,   842,  1480,  1387, -1939, -1939,
     346, -1939,  1496, -1939,  1479, -1939,   346, -1939,  1378,   982,
   -1939, -1939,     5, -1939, -1939,  1501, -1939,  1494,  1503,   849,
   -1939,   346,  1492, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939,  1493, -1939, -1939,   378,  1497,  1502,  3681,  2568,
     -86, -1939,  1486, -1939, -1939,   851, -1939, -1939, -1939, -1939,
   -1939,   856, -1939,  1495,   857, -1939, -1939, -1939,  2740, -1939,
    1162, -1939, -1939, -1939,   873, -1939,  1512, -1939,  1263,  1507,
    1517,   880, -1939, -1939, -1939,  1519, -1939,  1515,  1518,  1506,
     346,  2740,  2740, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
    1528,  1531, -1939,   437, -1939, -1939,  3717,  3796, -1939,  1520,
   -1939,   468,  1523, -1939, -1939, -1939, -1939,   487, -1939, -1939,
   -1939,   499, -1939,   504,   506,   508, -1939,   526, -1939,   535,
   -1939,  1525,  1533,  1534,  1536, -1939,  1537,  1538, -1939, -1939,
   -1939, -1939, -1939, -1939,  1394,  1546,  1535, -1939,  1544,   -57,
     887, -1939,  1540,  1542, -1939, -1939,  1552,  1554,  1555, -1939,
   -1939, -1939, -1939, -1939, -1939,   733,   346,    94, -1939,  1556,
   -1939,  1569, -1939,  1406, -1939, -1939, -1939,  1561, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939,   298, -1939, -1939, -1939,
     346,  1406,   121,  1409, -1939, -1939,   346,   346, -1939,   807,
     379, -1939,  1562, -1939,  1522,  2740,  2785, -1939,  2740,  1469,
    1469,   634,   634,  1904,   737,  2187,  2806,  5264,  2806,  2806,
    2806,  2806,  2806,  2187,  1563,  1469,  1563,  5295,  1462, -1939,
   -1939,  1566,  1551,  2342, -1939, -1939, -1939, -1939, -1939,  1575,
   -1939, -1939,   718,  5264, -1939,  2740, -1939, -1939, -1939, -1939,
    5264,   433,  5264,  1473,  1473,   913,  1473,   667, -1939,  1476,
    1581,   314,  3877,  1582,  1588,  1589,  2785,  2785,  2785, -1939,
   -1939,   346,  1584, -1939,  1586,  1417, -1939,   479, -1939, -1939,
   -1939, -1939,  1347,   813,   859, -1939,   889,   718, -1939,   718,
     919,  5264,  1596,   926, -1939,  5264,  2740,  2397, -1939,   931,
   -1939,   718,  1463, -1939,   904,   909, -1939,   933,  1599,  1445,
     934, -1939,  2105, -1939,    83, -1939,  1592,   346,   346,  2740,
     346, -1939, -1939,  1406, -1939, -1939, -1939,  1370,   346,  2740,
     346, -1939,   346, -1939,  1394,  2740,  1591,  2568, -1939, -1939,
   -1939, -1939,   945, -1939,  1597, -1939,  1601,  1602,  1604,  1413,
    2740,   346,   346, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
     825,   346, -1939,  2695,  2869,  1593,   346,   346, -1939,   346,
   -1939,   -51,   346, -1939,  2740,   346, -1939,  1463,  5264, -1939,
    1612,   146,  1612, -1939,   346,  1263,  1615,  2711,   346,   346,
   -1939,   445,  2740,   670,  2740,   957, -1939,  1608,  5264, -1939,
      26, -1939, -1939, -1939, -1939, -1939,   825,    54, -1939,   346,
   -1939,   789, -1939, -1939,   -20, -1939,   325,   852, -1939,   812,
   -1939,   453, -1939,   -67, -1939,   346,   346,   346, -1939,   346,
     346,   743, -1939,   346, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939,   346, -1939, -1939,   346,   346,   346, -1939, -1939, -1939,
   -1939, -1939,   346,   693, -1939, -1939,  1613, -1939,  1622, -1939,
   -1939,  1569, -1939, -1939, -1939, -1939,  5264,  2119, -1939, -1939,
   -1939,   538,    68,    68,  1389,  1390, -1939, -1939,  1392,  1395,
    1396,   582,   346, -1939, -1939, -1939, -1939,  1625, -1939, -1939,
   -1939,  1562, -1939,  1631, -1939,   630,  1618, -1939,  1628,  3911,
   -1939,  1619,  1623,  1387, -1939, -1939,  3947, -1939,  2740,  2740,
    1267, -1939,  5264,  1345,   314, -1939,   138,  2785,  2785,  2785,
     184, -1939,   210, -1939,   356, -1939,  1406,   346, -1939,  1462,
   -1939, -1939,  1637,   965,  2740, -1939,  1641, -1939,  5264, -1939,
   -1939, -1939,  2740, -1939, -1939,  1642,  2740, -1939, -1939, -1939,
   -1939,  5264, -1939,  1445,  2740,  1629, -1939,  1630,  1632,  3981,
    1644, -1939,   164,   346, -1939,   990, -1939, -1939,  1634,  5264,
   -1939, -1939,  3947, -1939,  1378, -1939,  1378,   346,   346,   346,
     997,  1009, -1939,   346,  1639,  1636,  2740,  4018,  2726, -1939,
   -1939, -1939,  1406,  1394, -1939, -1939,  1489,  1647,  5264, -1939,
     346, -1939,  1643,  1648, -1939, -1939,  1410,  1658, -1939, -1939,
    1660, -1939,  5264,  1021, -1939,  1038, -1939, -1939,  4057, -1939,
   -1939,  1055, -1939, -1939,  5264,  1651,   346, -1939, -1939,  1664,
    1667,  1465,  1614,   346,   346,  1657,  1675, -1939,   622, -1939,
    1669, -1939, -1939, -1939,  1671, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939,   789, -1939, -1939, -1939, -1939,   -20,   346, -1939,
   -1939,  1074,  1674, -1939,  1678, -1939,  1679, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939,   852, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
     812, -1939, -1939, -1939, -1939, -1939,   453, -1939, -1939, -1939,
     -67,  1676,  1683,  1684,   519,  1083, -1939,  1685,  1686,  1394,
   -1939,  1085,   893,  1097,  1111,  1112,  1114,  1687,  2740,  2740,
   -1939, -1939,  1688, -1939,  1680,   693,  2246, -1939,  1131, -1939,
    5264, -1939, -1939, -1939,  1692, -1939, -1939, -1939, -1939,   329,
     329,   329,   329,   329,   807, -1939,  1695,  1707,  1698,   807,
    1618, -1939,   379,   630,    87,    87, -1939, -1939, -1939,  1137,
    1708,  1184,   447, -1939,  1711,   630, -1939,  2740, -1939,  1697,
   -1939,  1387, -1939,  2342,  5264,  1700, -1939, -1939,  1091,  1696,
    1702,  1139,  1704,  1705,  1709, -1939, -1939, -1939,  1713,  1462,
    1712,    30,   718, -1939,  5264,   346,   825,  5264,    30,   346,
    5264,  1445,  2740,  1714,  5264,  1140, -1939, -1939, -1939, -1939,
   -1939,  2740, -1939,  1717, -1939, -1939, -1939, -1939, -1939,  1142,
    1165,  1166, -1939, -1939, -1939,   944, -1939,  5264,  2740,  2740,
    4095, -1939,   346, -1939, -1939,  1647, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939,  1710,   146,  1715,
    3046, -1939,   346,   346,   346,  2711, -1939, -1939, -1939,   670,
   -1939, -1939, -1939,  2440,   346, -1939, -1939,  1716,  1729, -1939,
     346,   346,  2740, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939,   325, -1939, -1939, -1939,  2740, -1939,
    2740, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939,  1723,  1725, -1939, -1939, -1939, -1939, -1939, -1939,  5264,
    5264,  1176,  1735, -1939, -1939, -1939,  1724,  4126, -1939, -1939,
   -1939,   538, -1939, -1939, -1939, -1939, -1939, -1939,   807, -1939,
     346, -1939, -1939,  1732,  1718, -1939,  1160,   447,   447,   630,
   -1939,   630,    87,    87,    87,    87,    87,  1186,  4157, -1939,
   -1939, -1939, -1939,  2740, -1939, -1939, -1939, -1939,  1654,  1727,
    1020, -1939,   346,  1741,  1414,   346, -1939,   346, -1939, -1939,
    4188, -1939,  2740, -1939,  4219,  1508,  2740, -1939, -1939, -1939,
   -1939,  1187, -1939, -1939,  5264,  5264,  2740,  1740, -1939,    36,
   -1939,  2740, -1939,  1736,  1739, -1939, -1939,  1746,  1756, -1939,
   -1939, -1939, -1939, -1939,  1649,  1745,  1188,  1762,  1764,  1197,
     878,   346,   346, -1939, -1939,  5264,   216,  1754,   334, -1939,
   -1939,  1742, -1939, -1939,   365,  4257,  4298, -1939, -1939, -1939,
   -1939, -1939,   346,   346,   893,  1775,  1777, -1939, -1939, -1939,
    1409,  1765, -1939,  1462, -1939,   630, -1939,  1186,  1769,   447,
     447, -1939, -1939, -1939, -1939,  4350, -1939,  3947, -1939,  1198,
   -1939,  1050, -1939,   718,  1546, -1939,  1445, -1939,  1530, -1939,
    1776,  4381,   944, -1939,  5264,  2261,  1780,  1781,  1783,  1789,
    1790,  1791,   346,   346,  1792,  1793,  4415, -1939, -1939, -1939,
    2740,   346,   346, -1939, -1939,  1794,   346, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939,  1785, -1939, -1939, -1939,
   -1939, -1939,  1199, -1939, -1939, -1939, -1939,  1795, -1939, -1939,
     554,  1802, -1939, -1939,  1806, -1939, -1939,  1796,  1202,  1186,
   -1939,  2740,  1654, -1939, -1939,  2740,   346,  2740, -1939, -1939,
   -1939,  5264,  1204, -1939, -1939,  1780,   346,   346,   346,   346,
     346, -1939, -1939,  2740,  2740,  2740,  1209, -1939, -1939,  1807,
   -1939,  1214,  1811,  1221,   346,  2740, -1939, -1939, -1939, -1939,
    2740,   346,  1798, -1939, -1939,  4493, -1939,  5264, -1939, -1939,
    1799,  4527,  2261, -1939,   361, -1939,  1814,  1239,  1240,  1815,
    1241,  1809,  1258,  4742,  5068,  1808,  5106, -1939,   346,  1749,
   -1939, -1939, -1939, -1939,  1546, -1939,  5137,  5168,   940, -1939,
    1820, -1939, -1939,  2740,  1967, -1939, -1939,  1823,  1824,   346,
     346, -1939, -1939,   346, -1939,  2740, -1939, -1939,  2740, -1939,
    2740, -1939,  1816,  1270,  1279, -1939, -1939,   346,  5264,   346,
    5264,  1281, -1939, -1939, -1939, -1939,  1284, -1939,  1817,  1290,
    1291,  1298,  5199,  5264, -1939, -1939, -1939, -1939, -1939,  1818,
    1967, -1939,   346, -1939,  2740, -1939, -1939,  1822,  2740,  2740,
    1827, -1939, -1939, -1939,  5233,  1299, -1939, -1939,  5264, -1939,
    2740,  2740,  2740,  1826, -1939,  5264, -1939, -1939,    33,  1321,
   -1939,  1832,  1841, -1939,  1834,  1834,  1834, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939,   493,  1844, -1939,  1726,
   -1939,  1324, -1939, -1939, -1939
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1939, -1939, -1939, -1939, -1939,    24,  1640,   992, -1939, -1939,
    -640,   -52, -1939, -1939,  -364, -1939,   640, -1939,   -50,   987,
   -1939, -1939, -1939,  2221,   -34, -1939, -1939, -1939, -1939, -1939,
   -1939,    98,   366,   717, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939,  -148,  -863, -1939, -1939, -1939,   816,   367,  1323,
   -1939,  -231, -1481,   105, -1939, -1939, -1939, -1939, -1939, -1939,
    1320,  -274,  -277, -1939, -1939, -1939,  1327, -1939,  -405, -1939,
   -1939, -1939, -1939,  1203, -1939, -1939,   635, -1207, -1458,   986,
     344, -1468,  -227,  -121,   991, -1939,    91,   100, -1715, -1939,
   -1463, -1186, -1461,  -392, -1939,   -96, -1508, -1562, -1264, -1939,
   -1939,   456,   775,   248,  -162,     3, -1939,   477, -1939, -1939,
   -1939, -1939, -1939,  -177, -1939,   -14,  -207,   914, -1939,   896,
     550,   575,  -355, -1939, -1939,   858, -1939, -1939, -1939, -1939,
     295,   296,  1853,  2562,  -301, -1245,   107,  -450, -1347,  1096,
    -541,  -607,  1626,   297,  1499,  -961,    97, -1939, -1939,  -594,
    -574,  -223, -1939,  -830, -1939,  -536,  -907, -1083, -1939, -1939,
   -1939,    89, -1939, -1939,  1257, -1939, -1939,  1703, -1939,  1706,
   -1939, -1939,   597, -1939,  -356,    18, -1939, -1939,  1719,  1721,
   -1939,   561, -1939,  -704,  -193,  1182, -1939,   993, -1939, -1939,
    -203, -1939,   946,   387, -1939,  4557,  -383, -1051, -1939, -1939,
   -1939, -1939, -1939, -1939,   989, -1939,   388,  -839, -1939, -1939,
   -1939,   363, -1240,  -579,   988,  -765,  -365,  -399,  -417,   427,
     -32, -1939, -1939, -1939,  -623, -1939, -1939,   910, -1939, -1939,
     881, -1939,  1145, -1846,   823, -1939, -1939, -1939,  1325, -1939,
    1335, -1939,  1336, -1939,  1334,  -971, -1939, -1939, -1939,  -192,
    -266, -1939, -1939, -1939,  -384, -1939,  -382,   606,  -321,   605,
   -1939,   -69, -1939, -1939, -1939,  -366, -1939, -1939, -1939, -1692,
   -1939, -1939, -1939, -1939, -1939, -1385,  -543,    73, -1939,  -236,
   -1939,  1200,   995, -1939, -1939,  1003, -1939, -1939, -1939, -1939,
    -337, -1939, -1939,   930, -1939, -1939,   978, -1939,   143,   994,
   -1939, -1939, -1939,   567, -1939, -1939, -1939,  -271, -1939, -1939,
     110, -1939,  -746,  -371,  -353, -1939, -1939, -1939, -1430, -1939,
   -1939, -1939,  -233, -1939, -1939,  -346, -1939,  -363, -1939,  -380,
   -1939,  -381, -1651, -1032,  -733, -1939,  -169,  -462,  -933, -1938,
   -1939, -1939, -1939,  -461, -1437,   326, -1939,  -695, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939,  -458, -1397,   565,
   -1939,   101, -1939,  1368, -1939,  1543, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1380,   632, -1939,  1302, -1939,
   -1939, -1939, -1939,  1690, -1939, -1939, -1939,   181,  1646, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,   557,
   -1939, -1939, -1939,   134, -1939, -1939, -1939, -1939,   -94, -1809,
   -1939, -1939, -1939, -1939, -1939,   516,   322,  -499, -1181,  -871,
   -1291, -1390, -1389, -1386, -1939, -1361, -1359, -1257, -1939, -1939,
   -1939, -1939, -1939,   304, -1939, -1939, -1939, -1939, -1939,   349,
   -1358, -1357, -1939, -1939, -1939,   305, -1939, -1939,   347, -1939,
     341, -1939, -1939, -1939, -1939,   316, -1939, -1939, -1939, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,
   -1939,   124, -1939,   128,  -129, -1939, -1939, -1939, -1939, -1939,
   -1939, -1939,   874, -1939, -1939, -1939,  -817, -1939,   111, -1939,
   -1939, -1939, -1939, -1939, -1939, -1939, -1939, -1939,   863, -1939,
   -1939, -1939,   862, -1939, -1939, -1939, -1939,   861, -1939
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1163
static const yytype_int16 yytable[] =
{
     391,   788,   675,   664,   649,   974,   697,   939,   792,   957,
     403,   403,   800,   801,   802,   803,  1415,   411,  1054,   559,
     561,  1631,   840,  1244,   614,   566,   688,  1334,   614,  1288,
    1198,   943,  1615,  1552,  1778,   771,   703,  1811,   706,   907,
    1067,  1665,  1532,   709,   710,   711,   437,   715,   973,  1658,
    1355,   712,   538,  1630,   714,   645,   716,  1764,  1781,  1766,
    1783,  1761,  1371,  1537,   763,  1427,  2053,  2076,   456,  1150,
     733,  1565,   459,  1801,  1797,  1043,   783,  2146,  1816,  1731,
    1732,   405,  1151,  1733,  2001,   968,   968,  1206,  1025,  1416,
     969,   969,   669,   764,   823,   668,   931,  1679,  1765,   866,
     418,   986,  1803,  1295,   654,  1285,  1285,  1679,  1734,  1846,
    1735,  1737,  1738,   719,     2,     3,  -561,   826,  1396,   828,
     565,   696,  -541,   439,  1689,  1486,   829,   830,   831,   744,
     635,   636,   834,   835,   836,   837,  1512,   838,   839,  1316,
     454,  1026,  2169,   760,  -591,   532,  -592,   383,   765,   866,
     683,  -582,   773,   560,   776,   565,  -591,  1436,  -592,   402,
    1528,  2374,  -527,   552,   957,   867,  2202,   795,   481,  1027,
     541,  2147,  1862,   638,  1396,   639,  1720,   354,  1730,   809,
    1743,   812,  -527,   402,   383,   386,  1193,   705,   818,   383,
    2375,   950,  -585,  1652,   782,   952,   946,  1869,  1870,  1871,
     567,  1315,   959,   383,  -585,  1396,     8,   565,   565,  1028,
    1726,   384,  1736,  1397,  1744,  1691,   402,  1529,  -589,   958,
    1029,  2172,   960,   402,  -561,   402,  1684,  2148, -1087,   614,
    -589,  1398,  2173,  2174,  1680,  1417,  1806,  1125,  2175,   942,
    2176,  -772,  2007,  2008,  1680,  2149,  1703,  -582,  1030,  2177,
    2376,  2178,  -591,  2179,  -592,  1207,  -137,  2150,  1487,  2151,
    2152,  1488,  2153,  -541,     4,  2154,   778,  1163,   876,  1530,
     588,   402,   386,   402,  1208,   402,  -527,  1068,   888,   889,
     890,   891,  1197,  2112,   565,   892,  1718,  1398,  1728,  1455,
    1741,  -339,  1747,  -141,   402,  2006,   997,   402,   -61,  -339,
    -585,   402,   640,   643,  1623,  1508,  1509,  1002,   650,   651,
     655,   651,  1034,   659,   661, -1112, -1034,   667,  1398,   671,
     673,   673,   676,  1653,  1565,   679,  -589,   932,   684,   962,
     679,  1130,  2002,  2053,  1840,   695,  1785,  1787,   700,   421,
     679,  1031,   679,   957,  2004,   957,   403,   679,   679,   679,
    1731,  1732,   957,  1120,  1733,   679,  2155,   713,   679,  1055,
     679,   565,  1708,  1289,  -587,  -561,   724,   725,   987, -1087,
    1119,     5,  1121,   736,   738,  2180,  -587,   743,  2181,  1734,
     402,  1735,  1737,  1738,   750,   614,   402,   754,  -582,   614,
     402,  1006, -1123,  -591,  1250,  -592,   614,  -137,  1127,   767,
      46,  1128,   774,  -339,  1517,  1454,  1107,   565,   695,   784,
     786,   786,  1513,   790,   767,  1388,   708,  1452,  1863,   796,
     798,   798,   798,   798,   798,  1313,   807,   984,  2188,   811,
     969,   813,   750,    74,  -141,   816,  1720,   565,   819,   -61,
     985,  -585,   824,   402,  1558,  1447,  1146,   991,  -563,  1730,
    2119,  2120,  2014,  1383,   402,  1743, -1112, -1034,   402,  2331,
    1005,  1776,  1777,  2182,  1659,   565,    96,  -589,   665, -1139,
    1726,   841,  -587,  1015,   842,   402,   565,  1013,   588,   849,
     854,   860,   666,  1736,  2015,  2323,  1016,   868,  1117,  1744,
     873,   874,   875,   667,   477,   565,   109,   878,   881,   882,
    1242,  2117,   887,   667,   667,   667,   667,   565,   402,  2297,
     895,   896,   565,   957,   565, -1142,   565,  2079,  2066,  1243,
    1596,  2183,  2184,  2185,  1287,  1407,  1408,   933,  1781,   569,
    1783,  2323,  1145, -1123,   565,  1147,  1303,  1304,  1305,  1306,
    1307,  2298,  2114,   565,   613, -1076,  1718,   614,   613,  -563,
    1050,  1571,  1573,  1575,  1522,  1523,  2194,   933,  1409,  1728,
     863,   864,  -563,   570,  2189,  1741,  1278,   546,   547,  1747,
    1248,  1202,   879, -1106,   402,  2249,   684,   975,   736,   790,
     784,   671,   980,  1060, -1086,   813,   982,  1532,  1203,   402,
    1794,   883,  2000,   667,  2029,   487,  1719,   558,  1729,  1249,
    1742,   884,  1748, -1111,   993,  2134,  1148,  2209,  1537,   588,
   -1139,   679,  -527,  -587,  1004, -1033,   667,  1158,  2190,  1795,
   -1122,  2374, -1138,  1160, -1141,   933,  -527,  1166,  1231,  2191,
    1528,  1232,  1172,  1012,  1180,  1176,  1178,   488,   942,   912,
    1022,  1364, -1075,   913,  1689,  1803,  1804,  1805,  1922,  1359,
    2375, -1105,  1372,  2195,   933,    50, -1142,  2359,  1751,  1752,
    1753,  1690,  1757,  1758,  2196,  1044,  1221,  1049,  2364,  1118,
    1051,   928,   953,  2201,   617,  1669,   954,  1550,   625,   665,
    1245,  1054,  1062,  1065,   548,  1604, -1076,  1529,   529,  1246,
    -563,  1247,  1094,   666,   530,  1095,   957,   957,   957,   957,
     957,  1101,  1100,  1102,   956,  1023,  1067,  1067,  1109,  1142,
    1113,  1768,   721,   667, -1106,   968,   534,  1551,  1024,  1769,
     969,  1295,  1143,  1204,  2252, -1086,   640,   531,  2388,  2390,
     614,   614,   614,   614,   614,  1691,  1205,  1065,  1692,  1530,
     758,  2394,   912,   667, -1111,  1435,   913,   766,   539,   613,
    2121,  2122,  2123,   914,   915,   118, -1033,   667,  1209,   402,
     667, -1122,   122, -1138,  1852, -1141,  1154,  1153,  1319,  2241,
     542,  1210,  1212,  1320,   928,  1570,  1572,  1574,  1461,  1806,
     969,   969,   969, -1075,  1464,  1213,   543,  1217,  1467,   544,
    1469,  2000, -1105,  2272,  1471,  1290,  1473,  2268,  1199,  1447,
    1218,  1447,  1571,  1573,  1575,  1296,  1347,  1351,  1291,  1322,
     565,  1214,   811,  2236,  2284,  1363,  -382,  -527,  1297,  1348,
    1352,   568,  1521,  1522,  1523,   545,   953,  1239,  1578,   953,
     954,  2270,   383,   954,  1524,  1952,  1953,   609,   610,   551,
     609,   610,  1301,  1525,   955,  1308,  2267,   955,  1323,  1251,
    1380,  1499,  1254,  1324,  1325,   554,  1719,  1402,   956,  1419,
    1326,   956,  -383,  1381,  1422,  1425,  1526,   648,  2207,  1729,
    1403,  1527,  1420,   555,  1579,  1742,   556,  1423,  1426,  1748,
    1334,   984,  1992,  1993,  1994,  1995,  1996,  1355,  1439,  1216,
    1181,  1182,   557,  -384,  1433,  1489,  1712,  1580,  1106,  1528,
    1959,  1440,  1960,   562,  1240,   613,  2330,  -382,  1490,   613,
    1581,  1961,  -383,  1962,  1988,  1959,   613,  1960,   953,   931,
    2329,   963,   954,  1183,   934,  1560,  1961,  1584,  1962,   609,
     610,  1563,   640,   563,  1015,  1332,  1712,  1561,  1338,  1290,
    1585,  1593,  1598,   933,   655,  2128,  1897,  1587,  -841,  1669,
     956,  2050,  1590,  1624,  1594,  1599,  1529,   676,  1462,  1285,
    1285,  1285,  1285,  1285,  1465,  1676,  1625,   564,  1468,  1518,
    1470,  1468,  1468,  1351,  1472,  1616,  1474,  1617,  1677,   622,
    1689,  1447,  1582,  1373,  1558,  1825,  1843,    25,   700,   608,
     609,   610,    29,  1612,  1327,   604,  1591,  1690,  1584,   619,
    1603,   583,  2032,  1689,   725,  1584,   627,   402,  1530,  2037,
     585,  1866,  1596,  1399,    47,    48,  1505,  1402,  1872,   738,
    1690,   628,  1614,  -387,   629,  1328,  1831,  1572,  1574,  1905,
    1873,   969,   969,   969,  1511,   937,  1963,  1964,   586,  1965,
    1966,  1646,  1906,  1689,   630,    25,  1439,  1608,   536,  1610,
      29,  1963,  1964,  -385,  1965,  1966,  1421,  1184,  1185,  1907,
    1690,  1186,  1187,  1909,   631,   937,   587,   613,    90,  1329,
    1967,  1691,    47,    48,  1692,   632,  1910,  1713,    95,  1693,
    1702,   633,  1934,  1707,   634,  1967,  1727,  1694,  1740,   637,
    1746,  1954,  1750,  1483,  1691,  1935,   953,  1692,   686,  1450,
     954,  1714,  1693,   611,  1955,  1973,  1958,   609,   610,  1633,
    1694,  1715,  1968,   646,   955,   647,  1716,  1713,  1974,  1676,
    1439,   662,  1676,   588,   121,  1969,    90,  1968,   956,  2128,
    1786,  1788,  1975,  1976,  1691,  1977,    95,  1692,   670,  1989,
    1969,  1714,  1481,  1194,  1194,  2009,  1828,  -585,  2042,  1592,
    1483,  1715,  1990,   682,   849,  1683,  1716,   537,  2010,   854,
    1820,  2043,   860,  2047,  1500,   868,  1611,   953,   150,  1164,
    1165,   954,  1168,  1483,  1483,   589,  2012,  2013,   609,   610,
     689,  2116,   121,  1429,  2105,   955,  2048,  2049,  1510,  1823,
    1923,  -230,  1925,  1926,   667,  2142,  1142,  2106,  1251,   956,
    2012,  2013,  2012,  2013,  1930,  1439,  2212,  2245,  2143,  2165,
    2009,   698,  2262,  1839,  1937,  1841,  1939,  1584,  2167,  2213,
    2246,   957,  1439,  2254,  1650,  2263,  2038,  2020,  1848,  2282,
    2277,   576,   577,  1851,  1017,  2280,  1018,   704,   620,   578,
     624,   626,  2283,   579,   580,   581,   582,  1402,  1483,  1439,
     613,   613,   613,   613,   613,   732,   583,  1865,   963,   963,
    2301,  2302,  2304,   584,   606,   585,  1676,   717,   607,  1576,
     722,  1517,  1292,   755,   608,   609,   610,   578,  1973,  2306,
     735,   579,   580,   581,   582,   758,   583,  1973,   741,  2340,
     742,  2335,  2342,   586,   583,   585,   753,  2215,  1402,  1439,
    2336,   584,  2341,   585,   745,  2343,  1142,  2362,   758,    25,
     748,  2345,  2346,   865,    29,  1606,  1606,  1928,  1606,  2347,
    2363,   587,  1931,   586,  1309,  1310,   679,   749,  1044,  2377,
    1044,   586,  1554,  1618,   757,  1941,    47,    48,   592,   877,
     614,   761,  2378,  2383,  2384,  2393,   762,  1384,  2313,  2314,
     944,   587,  1174,  1175,   945,   789,   797,  1943,   402,   587,
     770,   609,   610,  1945,  1641,   821,   822,  1947,   825,  1835,
     827, -1162,   583,  1113,  1832,  1833,  1834,   846,   588,  1654,
     847,   585,  1298,  1656,   848,   880,  1299,   578,   611,   667,
      90,   579,   580,   581,   582,   904,   402,   933,   934,   935,
      95,  1681,   937,  1682,   583,  1685,   940,   936,   588,   586,
     951,   584,   961,   585,  1514,   981,   588,   778,   990,   578,
     992,   994,   996,   579,   580,   581,   582,  1003,  1754,  1009,
     589,  1014,   386,   946,  1038,  1881,   583,   587,  1035,  1199,
    1040,   586,  1762,   584,   931,   585,   121,  1056,  1057,  1058,
    1767,  1063,  1071,  1072,  1126,  1137,  1099,  1095,  1149,  1774,
     589,  1140,  1155,  1152,  1163,  1192,  1169,  2238,   589,   587,
    1211,   565,  1258,   586,   611,  1219,  1255,  1059,   913,  1279,
    1796,  1280,   954,  -342,  1311,  1317,  1318,  2033,  1382,  1339,
     150,  1342,  1350,  1807,   588,  1358,  1365,  1366,  1367,  1368,
    1369,   587,  1370,  1379,  1385,  1387,   402,  1391,  -920,  1400,
    1401,   946,  1618,  1405,  1406,  1618,  1618,  1618,  1410,  1434,
    1411,  1424,  1437,  1418,  1438,  1836,   588,  1441,   746,  2074,
    1442,  1067,  1444,  1443,  2271,  1447,  1451,  2020,   402,  1453,
    1475,  1460,  2086,  2078,  1463,  2035,   589,  2089,  1476,  1477,
    2090,  1478,  1479,  1480,  1483,  1491,  1484,  1492,   588,  1554,
    2097,   679,  2098,   793,  2099,  1485,  2100,  1494,   912,  1495,
    1496,  1502,   913,   804,   883,   946,  1507,  1545,   589,   914,
     915,  1874,  1559,  2311,  1548,   916,   917,  1553,   919,  1564,
    1567,   921,   922,   923,   924,   925,  1568,  1569,  1051,   354,
     928,   384,  1577,  1586,  2328,  1067,  1595,  1604,   963,  1613,
     589,   946,  1621,  1626,  1640,   769,  1627,  1628,  2168,  1629,
    1651,  1397,  1660,  1678,  2110,   770,   609,   610,  1771,  1773,
    1799,  1916,  1917,  1815,  2113,  1789,  1790,   583,  1791,  1802,
    1820,  1792,  1793,  1817,  1821,  1842,   585,  2328,  1845,  1849,
    1857,  1858,  1861,  1859,  1875,  1883,  1933,  1876,  1899,  2126,
    -494,  1413,  1882,  1900,   578,  1902,  1903,  1904,   579,   580,
     581,   582,  1911,  1680,   586,  1920,   906,   908,   909,  1914,
     910,   583,  1915,  1921,  1924,  1679,  1927,   911,   584,  1936,
     585,  2231,  2232,  1938,  1940,    13,    14,  1949,    15,    16,
    1991,   793,   587,    20,  1950,  1951,  1956,  1957,  1978,  1983,
    -381,    23,  1998,  1999,  1643,  2011,    27,  2019,   586,    30,
    2016,  2022,  2023,  2024,  1222,  2025,  2026,    37,  2028,    38,
    2027,    40,  2046,  2030,  2081,  2041,  2061,  2082,  2102,   611,
    2103,  2063,  2107,   989,  2115,  2108,   587,  -224,  2131,  2133,
    2003,  1807,  1807,  1807,    59,  2145,  1688,  2158,   999,   588,
    2159,  2160,  2140,  1807,  2161,    70,  2164,  1223,  2266,  -832,
    2269,  2166,  1194,  1194,  1194,  2187,  1194,  1194,  2214,  2193,
    1759,  2162,  2203,   402,  2204,  2216,  2206,  1021,  1194,    85,
    2210,  2217,  2244,   655,  1037,  2224,  2226,   684,  2227,  1225,
    1041,  1042,    93,   588,  2228,  2229,  2230,  2233,  2234,  2240,
    2250,   589,  2045,  2251,  2294,  2278,  2248,  2253,  2281,  2292,
     102,  2300,  2303,  1226,  2305,  1227,   104,  2312,  2317,  2309,
    2324,  2325,  2344,  2059,   108,  2349,   110,  2334,   112,  2379,
     114,  2367,  2264,  2357,  2360,  1098,  1654,   119,  2380,  2381,
    1836,  2392,  2067,   549,  2374,   589,  1215,  1501,  1228,  1220,
     613,   963,  2077,  1229,   130,   131,  2064,  1230,  2083,  1685,
    1456,  1231,  1984,  1772,  1232,  1395,   885,  2088,  1775,  2205,
    1985,   894,   143,  1520,  1010,  1800,  2094,  1252,  2208,   575,
    2118,   897,  1253,  2005,  1997,  2111,  1233,  1667,  1432,  1898,
    2157,  2062,  1649,   155,  1754,  2171,   156,  2084,  1343,   912,
    1234,  1361,  1600,   913,  1583,  1390,  1235,  1156,  1157,  1867,
     914,   915,  1868,  2104,  1194,  1194,  1194,   917,   417,   919,
    2021,  2391,   921,   922,   923,   924,   925,  2036,  2031,  1011,
     571,   928,   759,   572,  1589,  1116,  1620,  1826,  1796,  1349,
    1376,  1827,  1404,  1144,  1314,   976,   573,  1807,   574,  1807,
    1807,  1807,  1807,  1807,  1807,  1449,   977,   979,   978,  2237,
    1602,  1605,  1669,  2137,  2352,  2065,  2256,   578,  1124,  1331,
    2337,   579,   580,   581,   582,  1330,  1389,  1353,  2034,  1645,
    1344,  2296,  2265,  2138,   583,  2060,  2353,  2385,  2387,  2366,
    2243,   584,  1912,   585,  1666,   983,  2072,  2319,  1259,  1260,
    1261,  1262,  1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,
    1271,  1272,  1273,  1274,  1275,  1276,  1277,   815,   786,  2170,
    1917,   586,  2039,   793,  1632,  1064,    13,    14,  1293,    15,
      16,   720,   707,  2073,    20,  1300,  1760,  1302,  2219,  1942,
    1946,  1929,    23,   658,  1932,  1948,  1944,    27,  2093,   587,
      30,  2091,  1312,  1807,  2247,  2101,  1482,  1493,    37,   720,
      38,  1497,    40,  1498,     0,     0,   720,     0,     0,     0,
       0,     0,     0,     0,   779,     0,     0,     0,  1341,     0,
       0,     0,     0,     0,  1345,    59,   402,     0,     0,     0,
     798,   798,     0,     0,     0,     0,    70,     0,     0,  2067,
    1017,  1021,     0,     0,     0,   578,   588,     0,     0,   579,
     580,   581,   582,     0,  1779,     0,     0,     0,     0,   578,
      85,     0,   583,   579,   580,   581,   582,     0,   758,   584,
       0,   585,     0,    93,     0,   758,   583,     0,     0,     0,
       0,     0,     0,   584,     0,   585,     0,     0,     0,     0,
       0,   102,     0,     0,  2258,     0,     0,   104,   589,   586,
       0,     0,     0,     0,  1065,   108,  1065,   110,     0,   112,
       0,   114,     0,   586,     0,     0,   893,     0,   119,     0,
    2279,     0,   912,     0,     0,  1414,   913,   587,     0,  2289,
       0,     0,     0,   914,   915,   130,   131,     0,     0,   916,
     917,   587,   919,     0,  1428,   921,   922,   923,   924,   925,
       0,     0,   927,   143,   928,   929,     0,     0,     0,     0,
       0,  1762,  1762,     0,   402,     0,     0,  1448,   804,     0,
       0,     0,     0,     0,   155,     0,     0,   156,   402,     0,
     720,  1986,     0,     0,   588,     0,   578,     0,     0,     0,
     579,   580,   581,   582,     0,  2289,  2220,  2338,   588,     0,
       0,   578,     0,   583,     0,   579,   580,   581,   582,     0,
     584,     0,   585,     0,     0,     0,     0,     0,   583,     0,
       0,   770,   609,   610,     0,   584,     0,   585,     0,     0,
       0,     0,     0,   583,     0,     0,   589,     0,     0,     0,
     586,     0,   585,     0,     0,     0,     0,  2368,     0,     0,
     589,     0,     0,     0,     0,   586,     0,  2368,     0,  2386,
    2389,     0,  1194,     0,     0,     0,     0,     0,   587,  1516,
     586,     0,  2389,  1047,     0,  1222,     0,     0,     0,  1413,
       0,  1549,   578,   587,     0,     0,   579,   580,   581,   582,
       0,  1066,     0,     0,     0,     0,     0,     0,   587,   583,
       0,     0,     0,     0,  1097,   402,   584,     0,   585,  1556,
       0,     0,  1103,  1104,     0,     0,     0,  1110,  1223,     0,
     402,  1562,     0,     0,  1224,   588,     0,     0,     0,  2200,
    1194,     0,     0,     0,   998,   611,   586,   578,     0,     0,
     588,   579,   580,   581,   582,  1066,     0,     0,     0,     0,
    1225,     0,     0,  1138,   583,   588,     0,     0,     0,     0,
       0,   584,     0,   585,   587,     0,     0,     0,     0,     0,
       0,     0,  1588,   999,  1226,     0,  1227,   589,     0,     0,
     578,  1159,     0,  1162,   579,   580,   581,   582,  1601,     0,
       0,   586,   589,     0,     0,  1609,     0,   583,     0,     0,
       0,   402,   720,   720,   584,  1341,   585,   589,     0,  1228,
       0,  1619,     0,  1622,  1229,     0,     0,     0,  1230,   587,
       0,   588,  1231,     0,     0,  1232,  1341,     0,     0,     0,
       0,     0,     0,     0,   586,     0,     0,     0,   946,  1637,
       0,     0,     0,     0,     0,     0,     0,  1233,  2075,     0,
    1648,     0,     0,     0,  1194,     0,   402,     0,     0,     0,
       0,  1234,   587,  1662,     0,     0,     0,  1235,  1668,     0,
    1674,  1194,     0,   589,     0,     0,   588,  2288,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1284,  1284,     0,     0,     0,     0,     0,     0,   402,
       0,     0,     0,     0,   356,  1413,     0,     0,   578,     0,
     362,     0,   579,   580,   581,   582,     0,   720,   720,   588,
     369,     0,     0,   371,     0,   583,   374,     0,   589,     0,
       0,     0,   584,   380,   585,     0,     0,   387,     0,     0,
       0,   390,     0,  1780,  1333,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   409,
       0,     0,   586,   413,   414,     0,     0,  1354,     0,   419,
     420,   589,     0,     0,     0,   425,   426,     0,   427,   428,
     429,   430,     0,   431,  1824,   793,  1293,     0,     0,     0,
     587,     0,   440,     0,     0,     0,     0,   444,     0,   446,
       0,     0,     0,   449,     0,     0,   720,   453,     0,   455,
    1844,     0,     0,     0,     0,     0,   461,     0,  1847,     0,
     465,     0,  1850,     0,   468,     0,   470,   402,     0,     0,
    1854,     0,  1636,   478,   480,   578,     0,   482,   483,   579,
     580,   581,   582,   489,     0,   490,     0,   588,  1661,   494,
       0,   578,   583,     0,     0,   579,   580,   581,   582,   584,
       0,   585,  1877,  1879,  1880,     0,   578,     0,   583,     0,
     579,   580,   581,   582,     0,   584,   521,   585,   523,     0,
     578,     0,     0,   583,   579,   580,   581,   582,     0,   586,
     584,     0,   585,     0,     0,     0,  1066,   583,     0,   589,
       0,     0,     0,     0,   584,   586,   585,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   587,     0,     0,
     586,     0,     0,     0,     0,   578,     0,     0,     0,   579,
     966,   581,   582,   587,   586,     0,     0,     0,     0,     0,
       0,   912,   583,   930,     0,   913,     0,     0,   587,   584,
       0,   585,   914,   915,   402,     0,     0,     0,     0,   917,
       0, -1163,   587,     0, -1163, -1163, -1163, -1163, -1163,     0,
     402,     0,     0,   928,   588,     0,     0,     0,     0,   586,
       0,     0,     0,     0,     0,   402,     0,     0,     0,     0,
     588,     0,     0,     0,  1979,  1980,     0,     0,     0,   402,
       0,     0,  1987,  1519,   912,   588,  1638,   587,   913,   578,
       0,     0,     0,     0,     0,   914,   915,     0,     0,   588,
    1639,   916,   917,   918,   919,     0,   589,   921,   922,   923,
     924,   925,   926,     0,   927,     0,   928,   929,     0,     0,
       0,     0,   589,  2018,   402,     0,     0,     0,     0,  1556,
       0,     0,     0,     0,     0,     0,     0,   589,     0,     0,
       0,     0,     0,     0,   588,     0,     0,   720,     0,     0,
       0,   589,     0,     0,     0,     0,     0,   692,  2040,     0,
       0,     0,     0,     0,     0,     0,     0,  2044,     0,     0,
       0,     0,     0,  1091,     0,     0,     0,   930,     0,     0,
       0,     0,   912,     0,  2054,  2055,   913,   578,     0,     0,
       0,     0,     0,   914,   915,     0,   589,     0,     0,   916,
     917,   918,   919,   920,     0,   921,   922,   923,   924,   925,
     926,  1662,   927,     0,   928,   929,  1047,     0,  1047,   804,
       0,     0,     0,     0,   930,     0,     0,     0,  2085,     0,
       0,     0,     0,     0,     0,   930,     0,  1066,  1066,     0,
       0,     0,     0,     0,  2095,     0,  2096,  1634,     0,     0,
       0,     0,     0,   720,     0,  1644,     0,     0,  1110,     0,
     817,  1073,     0,     0,     0,  1074,   578,     0,     0,     0,
     779,     0,  1075,  1076,  1066,  1066,     0,     0,  1077,  1078,
    1079,  1080,     0,     0,  1081,  1082,  1083,  1084,  1085,  1086,
    1087,  1088,     0,  1089,  1090,   720,     0,     0,     0,     0,
       0,     0,  1709,     0,     0,     0,     0,     0,     0,     0,
       0,   720,   720,   720,     0,   720,   720,     0,     0,   720,
       0,     0,     0,     0,     0,     0,     0,   720,     0,  2125,
    1066,  1066,  1066,     0,  2127,     0,     0,   930,     0,   930,
     930,   930,   930,     0,     0,     0,     0,     0,  1854,     0,
       0,     0,  2141,   912,     0,  1141,     0,   913,   578,     0,
       0,     0,  2144,     0,   914,   915,     0,  2156,  1798,     0,
     916,   917,   918,   919,     0,     0,   921,   922,   923,   924,
     925,   926,     0,   927,     0,   928,   929,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   930,     0,
     720,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1516,   912,     0,     0,
     930,   913,   578,     0,     0,     0,     0,     0,   914,   915,
     930,     0,     0,  1257,   916,   917,   918,   919,     0,     0,
     921,   922,   923,   924,   925,   926,     0,   927,     0,   928,
     929,  2221,   930,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   720,   720,   720,  1341,     0,   930,     0,
     912,     0,   930,   930,   913,   578,     0,     0,     0,     0,
       0,   914,   915,     0,     0,     0,  1337,   916,   917,   918,
     919,     0,     0,   921,   922,   923,   924,   925,   926,     0,
     927,     0,   928,   929,     0,     0,     0,     0,     0,     0,
       0,     0,  1066,     0,     0,     0,     0,  2255,  2127,     0,
       0,  2257,     0,  2261,     0,     0,     0,     0,     0,   930,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2273,
    2274,  2276,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2286,     0,   912,     0,  1346,  2287,   913,   578,     0,
       0,     0,     0,     0,   914,   915,     0,     0,  2221,     0,
     916,   917,   918,   919,     0,     0,   921,   922,   923,   924,
     925,   926,     0,   927,     0,   928,   929,   930,   930,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2318,
    2320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   804,     0,     0,  2332,     0,  2333,     0,     0,     0,
       0,     0,     0,     0,     0,  1284,  1284,  1284,  1284,  1284,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2320,     0,     0,     0,
    2354,     0,     0,  1241,  2358,  1674,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1674,  2365,  2354,     0,
       0,     0,     0,     0,     0,     0,     0,  1333,     0,     0,
       0,     0,     0,     0,  1354,     0,     0,     0,     0,     0,
     930,   930,   930,   930,   930,   930,   930,   930,   930,   930,
     930,   930,   930,   930,   930,   930,   930,   930,   930,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2057,     0,
       0,     0,     0,     0,   930,     0,     0,     0,     0,     0,
       0,   930,     0,   930,     0,     0,     0,     0,     0,   779,
       0,     0,     0,   930,     0,     0,     0,     0,     0,     0,
    1066,     0,     0,  1321,     0,     0,     0,     0,     0,     0,
       0,     0,   912,     0,  1362,     0,   913,   578,     0,     0,
    2092,     0,   930,   914,   915,     0,   930,     0,     0,   916,
     917,   918,   919,     0,     0,   921,   922,   923,   924,   925,
     926,     0,   927,   912,   928,   929,     0,   913,   578,     0,
       0,     0,     0,     0,   914,   915,     0,     0,     0,  1374,
     916,   917,   918,   919,     0,     0,   921,   922,   923,   924,
     925,   926,     0,   927,     0,   928,   929,     0,     0,     0,
     912,     0,     0,     0,   913,   578,  1798,     0,     0,     0,
       0,   914,   915,     0,     0,   930,  1377,   916,   917,   918,
     919,     0,     0,   921,   922,   923,   924,   925,   926,   930,
     927,     0,   928,   929,     0,   912,     0,     0,  2132,   913,
     578,   720,     0,  2135,     0,     0,   914,   915,     0,   930,
       0,  1378,   916,   917,   918,   919,     0,     0,   921,   922,
     923,   924,   925,   926,     0,   927,   912,   928,   929,     0,
     913,   578,     0,     0,     0,     0,     0,   914,   915,     0,
       0,     0,  1412,   916,   917,   918,   919,     0,     0,   921,
     922,   923,   924,   925,   926,     0,   927,     0,   928,   929,
       0,     0,   912,     0,     0,     0,   913,   578,   720,   720,
       0,     0,     0,   914,   915,     0,     0,   930,  1458,   916,
     917,   918,   919,     0,     0,   921,   922,   923,   924,   925,
     926,     0,   927,     0,   928,   929,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     930,     0,     0,     0,     0,     0,     0,   930,     0,     0,
       0,     0,     0,   930,     0,     0,  1506,     0,  1066,     0,
       0,     0,  1066,     0,     0,     0,     0,     0,     0,     0,
       0,   912,     0,     0,     0,   913,   578,     0,     0,   930,
       0,     0,   914,   915,     0,     0,     0,  1459,   916,   917,
     918,   919,   930,     0,   921,   922,   923,   924,   925,   926,
     930,   927,     0,   928,   929,     0,     0,     0,     0,     0,
     930,     0,     0,   930,     0,     0,     0,     0,     0,     0,
       0,     0,  1066,   720,  1066,  1066,  1066,     0,   930,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   930,
     720,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   912,   930,     0,     0,   913,   578,     0,   930,
       0,     0,     0,   914,   915,   930,     0,     0,  1566,   916,
     917,   918,   919,     0,  1066,   921,   922,   923,   924,   925,
     926,     0,   927,     0,   928,   929,   912,     0,     0,     0,
     913,   578,     0,     0,     0,  1066,  1066,   914,   915,  1066,
       0,     0,  1818,   916,   917,   918,   919,     0,     0,   921,
     922,   923,   924,   925,   926,     0,   927,     0,   928,   929,
       0,     0,   912,     0,  1638,     0,   913,   578,     0,     0,
       0,     0,     0,   914,   915,     0,     0,     0,  1066,   916,
     917,   918,   919,     0,     0,   921,   922,   923,   924,   925,
     926,     0,   927,     0,   928,   929,   912,     0,     0,     0,
     913,   578,     0,     0,     0,     0,     0,   914,   915,     0,
       0,   930,  1860,   916,   917,   918,   919,     0,     0,   921,
     922,   923,   924,   925,   926,     0,   927,     0,   928,   929,
       0,     0,     0,   912,     0,  1878,     0,   913,   578,     0,
       0,     0,     0,     0,   914,   915,     0,     0,     0,     0,
     916,   917,   918,   919,     0,   930,   921,   922,   923,   924,
     925,   926,     0,   927,     0,   928,   929,     0,     0,     0,
       0,     0,   912,     0,     0,   930,   913,   578,   930,     0,
       0,   930,     0,   914,   915,   930,     0,     0,  1908,   916,
     917,   918,   919,     0,     0,   921,   922,   923,   924,   925,
     926,     0,   927,     0,   928,   929,     0,     0,   930,     0,
     912,   930,  2056,     0,   913,   578,     0,     0,     0,     0,
       0,   914,   915,     0,     0,     0,     0,   916,   917,   918,
     919,  1091,     0,   921,   922,   923,   924,   925,   926,     0,
     927,   912,   928,   929,     0,   913,   578,     0,     0,     0,
       0,     0,   914,   915,     0,     0,     0,  2109,   916,   917,
     918,   919,     0,     0,   921,   922,   923,   924,   925,   926,
       0,   927,   912,   928,   929,     0,   913,   578,     0,     0,
       0,     0,     0,   914,   915,     0,     0,     0,  2124,   916,
     917,   918,   919,     0,     0,   921,   922,   923,   924,   925,
     926,     0,   927,   912,   928,   929,  2136,   913,   578,     0,
     930,   930,     0,     0,   914,   915,     0,     0,   930,     0,
     916,   917,   918,   919,     0,     0,   921,   922,   923,   924,
     925,   926,     0,   927,   912,   928,   929,     0,   913,   578,
       0,     0,     0,     0,     0,   914,   915,     0,     0,   930,
    2139,   916,   917,   918,   919,     0,     0,   921,   922,   923,
     924,   925,   926,     0,   927,     0,   928,   929,     0,     0,
       0,   930,   912,     0,     0,   930,   913,   578,     0,     0,
       0,     0,     0,   914,   915,   930,   930,     0,  2198,   916,
     917,   918,   919,     0,     0,   921,   922,   923,   924,   925,
     926,     0,   927,     0,   928,   929,     0,     0,     0,     0,
       0,     0,     0,   912,     0,     0,   930,   913,   578,     0,
       0,     0,     0,     0,   914,   915,   930,   930,     0,  2199,
     916,   917,   918,   919,     0,     0,   921,   922,   923,   924,
     925,   926,     0,   927,     0,   928,   929,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   930,     0,   930,     0,
       0,     0,     0,     0,     0,   912,     0,     0,  2211,   913,
     578,     0,   930,     0,     0,   930,   914,   915,     0,     0,
       0,     0,   916,   917,   918,   919,     0,   930,   921,   922,
     923,   924,   925,   926,     0,   927,   912,   928,   929,     0,
     913,   578,     0,     0,     0,     0,     0,   914,   915,     0,
       0,     0,  2218,   916,   917,   918,   919,     0,     0,   921,
     922,   923,   924,   925,   926,     0,   927,     0,   928,   929,
     912,     0,     0,  2235,   913,   578,     0,     0,     0,     0,
       0,   914,   915,     0,     0,     0,     0,   916,   917,   918,
     919,     0,   930,   921,   922,   923,   924,   925,   926,     0,
     927,     0,   928,   929,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   930,     0,   930,     0,
       0,     0,   930,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   930,   930,     0,   930,   912,     0,
       0,  2293,   913,   578,     0,     0,     0,   930,   930,   914,
     915,     0,     0,     0,     0,   916,   917,   918,   919,     0,
       0,   921,   922,   923,   924,   925,   926,     0,   927,     0,
     928,   929,   912,     0,     0,     0,   913,   578,     0,   930,
       0,   930,     0,   914,   915,     0,     0,     0,  2295,   916,
     917,   918,   919,   930,   930,   921,   922,   923,   924,   925,
     926,     0,   927,     0,   928,   929,     0,     0,     0,     0,
       0,   358,   359,   360,   361,   930,   363,     0,   364,   930,
     366,   367,     0,   368,     0,     0,   930,   370,     0,   372,
     373,     0,     0,   375,   376,   377,     0,   379,     0,   381,
     382,     0,     0,   389,     0,     0,     0,     0,   392,   393,
     394,   395,   396,   397,   398,   399,     0,   400,   401,     0,
       0,   406,   407,   408,     0,   410,     0,   412,     0,     0,
     415,   416,     0,     0,     0,     0,     0,     0,   423,   424,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   432,
       0,   434,     0,   435,   436,     0,     0,     0,   441,   442,
     443,     0,     0,   445,     0,     0,   447,   448,     0,   450,
     451,   452,     0,     0,     0,     0,   457,   458,     0,     0,
     460,     0,   462,   463,   464,     0,   466,   467,     0,     0,
     469,     0,   471,   472,   473,   474,   475,   476,     0,     0,
       0,     0,     0,     0,   484,   485,   486,     0,     0,     0,
       0,   491,   492,   493,     0,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     520,     0,   522,     0,   524,     0,   525,   912,   526,   527,
     528,   913,   578,     9,     0,     0,     0,     0,   914,   915,
      10,     0,     0,  2307,   916,   917,   918,   919,     0,     0,
     921,   922,   923,   924,   925,   926,     0,   927,     0,   928,
     929,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,    12,    13,    14,     0,    15,    16,    17,    18,    19,
      20,     0,   605,    21,    22,   618,     0,   621,    23,    24,
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
     192,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,   196,   912,   197,   198,  2308,   913,   578,     0,
       0,     0,     0,     0,   914,   915,     0,     0,     0,     0,
     916,   917,   918,   919,     0,     0,   921,   922,   923,   924,
     925,   926,     0,   927,     0,   928,   929,     0,     0,     0,
       0,   912,     0,     0,  2310,   913,   578,     0,     0,     0,
       0,     0,   914,   915,     0,     0,   902,   903,   916,   917,
     918,   919,     0,     0,   921,   922,   923,   924,   925,   926,
       0,   927,   912,   928,   929,     0,   913,   578,     0,     0,
       0,     0,     0,   914,   915,     0,     0,     0,  2315,   916,
     917,   918,   919,     0,     0,   921,   922,   923,   924,   925,
     926,     0,   927,   912,   928,   929,     0,   913,   578,     0,
       0,     0,     0,     0,   914,   915,     0,     0,     0,  2316,
     916,   917,   918,   919,     0,     0,   921,   922,   923,   924,
     925,   926,     0,   927,   912,   928,   929,  2348,   913,   578,
       0,     0,     0,     0,     0,   914,   915,     0,     0,     0,
       0,   916,   917,   918,   919,     0,     0,   921,   922,   923,
     924,   925,   926,     0,   927,     0,   928,   929,   912,     0,
    2361,     0,   913,   578,     0,     0,     0,     0,     0,   914,
     915,     0,     0,     0,     0,   916,   917,   918,   919,     0,
       0,   921,   922,   923,   924,   925,   926,     0,   927,   912,
     928,   929,     0,   913,   578,     0,     0,     0,     0,     0,
     914,   915,     0,     0,     0,     0,   916,   917,   918,   919,
       0,     0,   921,   922,   923,   924,   925,   926,     0,   927,
     912,   928,   929,     0,   913,     0,     0,     0,     0,     0,
       0,   914,   915,     0,     0,     0,     0,   916,   917,   918,
     919,     0,     0,   921,   922,   923,   924,   925,   926,     0,
     927,     0,   928,   929
};

static const yytype_int16 yycheck[] =
{
      50,   463,   373,   368,   359,   628,   388,   601,   466,   616,
      62,    63,   473,   474,   475,   476,  1099,    69,   722,   222,
     223,  1401,   521,   886,   247,   228,   382,   988,   251,   936,
     847,   605,  1379,  1278,  1515,   452,   392,  1545,   394,   580,
     735,  1438,  1249,   399,   400,   401,    98,   411,   627,  1434,
    1011,   407,   200,  1400,   410,   356,   412,  1494,  1521,  1496,
    1521,  1491,  1033,  1249,   447,  1116,  1875,  1913,   118,   815,
     423,  1311,   122,  1541,  1532,   715,   460,    41,  1546,  1469,
    1469,    63,   815,  1469,  1799,   626,   627,    41,     5,   175,
     626,   627,   369,   448,   493,   369,    15,    71,  1495,     5,
      76,   644,    15,   942,     8,   935,   936,    71,  1469,  1590,
    1469,  1469,  1469,   414,     0,     1,     8,   499,   169,   501,
       8,   387,   116,    99,   191,   182,   508,   509,   510,   430,
       7,     8,   514,   515,   516,   517,    15,   519,   520,     8,
     116,    58,  2080,   444,     8,   197,     8,     7,   449,     5,
       8,    20,   453,     8,   455,     8,    20,  1128,    20,   129,
      92,   128,    15,   215,   771,    21,  2104,   468,   144,    86,
     202,   135,     8,     5,   169,     7,  1467,    15,  1469,   480,
    1471,   482,    37,   129,     7,    15,    21,    15,   489,     7,
     157,   608,     8,    47,   460,   612,   166,  1627,  1628,  1629,
     232,   966,   619,     7,    20,   169,   116,     8,     8,   126,
    1467,    15,  1469,   208,  1471,   282,   129,   149,     8,   618,
     137,     5,   621,   129,   116,   129,   172,   191,   116,   452,
      20,   282,    16,    17,   208,   321,   149,   780,    22,   604,
      24,     7,  1804,  1805,   208,   209,   266,   116,   165,    33,
     217,    35,   116,    37,   116,   209,   116,   221,   315,   223,
     224,   318,   226,   257,   150,   229,    15,   287,   545,   201,
     149,   129,    15,   129,   228,   129,   129,   735,   555,   556,
     557,   558,    21,  1998,     8,   559,  1467,   282,  1469,  1152,
    1471,   129,  1473,   116,   129,  1803,   661,   129,   116,   129,
     116,   129,   354,   355,  1387,     7,     8,   663,   360,   361,
     362,   363,   696,   365,   366,   116,   116,   369,   282,   371,
     372,   373,   374,   177,  1564,   377,   116,   246,   380,    15,
     382,   789,  1800,  2142,  1579,   387,  1522,  1523,   390,    64,
     392,   258,   394,   950,  1802,   952,   398,   399,   400,   401,
    1740,  1740,   959,   770,  1740,   407,   320,   409,   410,   723,
     412,     8,    37,   937,     8,   257,   418,   419,   645,   257,
     769,   257,   771,   425,   426,   159,    20,   429,   162,  1740,
     129,  1740,  1740,  1740,   436,   608,   129,   439,   257,   612,
     129,   668,   116,   257,    15,   257,   619,   257,   782,   451,
      89,   783,   454,   129,  1243,  1151,   759,     8,   460,   461,
     462,   463,  1242,   465,   466,  1055,   398,  1150,   254,   469,
     472,   473,   474,   475,   476,   966,   478,     8,    94,   481,
     966,   483,   484,   122,   257,   487,  1727,     8,   490,   257,
      21,   257,   494,   129,  1283,  1140,   810,   650,    15,  1740,
    2012,  2013,     5,  1047,   129,  1746,   257,   257,   129,  2305,
     667,  1512,  1513,   247,  1435,     8,   155,   257,    23,   116,
    1727,   523,   116,     8,   524,   129,     8,   684,   149,   529,
     530,   531,    37,  1740,    37,  2294,    21,   539,   765,  1746,
     542,   543,   544,   545,    15,     8,   185,   547,   550,   551,
     883,  2009,   554,   555,   556,   557,   558,     8,   129,   148,
     562,   563,     8,  1120,     8,   116,     8,  1914,  1903,   884,
    1359,   305,   306,   307,    64,   147,   148,     3,  1991,   218,
    1991,  2340,   809,   257,     8,   812,   953,   954,   955,   956,
     957,   180,  2000,     8,   247,   116,  1727,   770,   251,   116,
      26,  1316,  1317,  1318,    16,    17,   191,     3,   180,  1740,
     536,   537,   129,   252,   230,  1746,   931,     7,     8,  1750,
       8,   191,   548,   116,   129,    21,   628,   629,   630,   631,
     632,   633,   634,   731,   116,   637,   636,  1794,   208,   129,
       8,     5,  1799,   645,  1839,    15,  1467,     8,  1469,    37,
    1471,    15,  1473,   116,   654,  2035,   813,  2115,  1794,   149,
     257,   663,    23,   257,   666,   116,   668,   824,   284,    37,
     116,   128,   116,   826,   116,     3,    37,   830,   191,   295,
      92,   194,   835,   683,   841,   838,   839,     8,  1003,     5,
     692,  1023,   116,     9,   191,    15,    16,    17,    26,  1014,
     157,   116,  1034,   288,     3,    95,   257,  2349,  1475,  1476,
    1477,   208,  1479,  1480,   299,   717,   873,   719,  2360,    18,
     722,    37,     5,  2103,   247,     5,     9,  1256,   251,    23,
     887,  1385,   732,   735,   124,    15,   257,   149,    15,   892,
     257,   894,   744,    37,    15,   745,  1303,  1304,  1305,  1306,
    1307,   753,   752,   755,    37,     8,  1401,  1402,   760,     8,
     762,    18,   415,   765,   257,  1256,   257,  1258,    21,    26,
    1256,  1560,    21,     8,  2205,   257,   778,    15,  2379,  2380,
     953,   954,   955,   956,   957,   282,    21,   789,   285,   201,
     443,  2392,     5,   795,   257,  1127,     9,   450,    15,   452,
    2014,  2015,  2016,    16,    17,   195,   257,   809,     8,   129,
     812,   257,   202,   257,  1603,   257,   818,   817,   975,  2166,
       8,    21,     8,   980,    37,  1316,  1317,  1318,  1160,   149,
    1316,  1317,  1318,   257,  1166,    21,     8,     8,  1170,     8,
    1172,  1998,   257,  2230,  1176,     8,  1178,  2227,   848,  1494,
      21,  1496,  1567,  1568,  1569,     8,     8,     8,    21,    43,
       8,   863,   864,  2160,  2244,  1022,     3,    15,    21,    21,
      21,     7,    15,    16,    17,     8,     5,   879,    15,     5,
       9,  2228,     7,     9,    27,   316,   317,    16,    17,     8,
      16,    17,    21,    36,    23,    21,  2226,    23,    82,   901,
       8,  1215,   902,    87,    88,     8,  1727,     8,    37,     8,
      94,    37,     3,    21,     8,     8,    59,   149,  2113,  1740,
      21,    64,    21,     8,    15,  1746,     8,    21,    21,  1750,
    1841,     8,  1789,  1790,  1791,  1792,  1793,  1848,     8,   865,
     147,   148,     8,     3,    21,     8,    84,     8,     8,    92,
      22,    21,    24,     8,   880,   608,  2303,     3,    21,   612,
      21,    33,     3,    35,  1777,    22,   619,    24,     5,    15,
    2300,   624,     9,   180,    15,  1290,    33,     8,    35,    16,
      17,  1296,   984,     8,     8,   985,    84,  1292,   990,     8,
      21,     8,     8,     3,   996,  2028,  1650,    21,     8,     5,
      37,     7,    21,     8,    21,    21,   149,  1009,  1161,  1789,
    1790,  1791,  1792,  1793,  1167,     8,    21,     8,  1171,  1246,
    1173,  1174,  1175,     8,  1177,  1380,  1179,  1382,    21,     5,
     191,  1676,  1337,  1035,  1823,  1559,    21,    63,  1040,    15,
      16,    17,    68,  1375,   228,    15,  1351,   208,     8,    15,
    1365,    27,  1841,   191,  1056,     8,     8,   129,   201,  1848,
      36,    21,  1851,  1063,    90,    91,  1223,     8,    21,  1071,
     208,     8,  1378,     3,     8,   259,  1567,  1568,  1569,     8,
      21,  1567,  1568,  1569,  1241,    15,   158,   159,    64,   161,
     162,  1423,    21,   191,     8,    63,     8,  1368,   124,  1370,
      68,   158,   159,     3,   161,   162,  1106,   314,   315,    21,
     208,   318,   319,     8,     8,    15,    92,   770,   144,   303,
     192,   282,    90,    91,   285,     8,    21,   265,   154,   290,
    1462,     8,     8,  1465,     8,   192,  1468,   298,  1470,     8,
    1472,     8,  1474,     8,   282,    21,     5,   285,   149,  1149,
       9,   289,   290,   129,    21,     8,    21,    16,    17,  1410,
     298,   299,   234,    15,    23,    15,   304,   265,    21,     8,
       8,    15,     8,   149,   200,   247,   144,   234,    37,  2212,
    1522,  1523,    21,    21,   282,    21,   154,   285,    15,     8,
     247,   289,  1192,   846,   847,     8,  1563,     8,     8,  1352,
       8,   299,    21,    15,  1204,  1456,   304,   233,    21,  1209,
      21,    21,  1212,    21,  1216,  1217,  1373,     5,   244,   828,
     829,     9,   831,     8,     8,   201,    16,    17,    16,    17,
       7,    21,   200,    21,     8,    23,    21,    21,  1240,  1554,
    1689,     7,  1691,  1692,  1246,     8,     8,    21,  1250,    37,
      16,    17,    16,    17,  1703,     8,     8,     8,    21,    21,
       8,    15,     8,  1578,  1713,  1580,  1715,     8,    21,    21,
      21,  1828,     8,    21,  1427,    21,  1849,  1821,  1593,     8,
      21,   238,   239,  1598,     5,    21,     7,    15,   249,    10,
     251,   252,    21,    14,    15,    16,    17,     8,     8,     8,
     953,   954,   955,   956,   957,     8,    27,  1613,   961,   962,
      21,    21,    21,    34,     5,    36,     8,    15,     9,  1321,
      15,  2110,     5,    37,    15,    16,    17,    10,     8,    21,
      15,    14,    15,    16,    17,   988,    27,     8,    15,     8,
      15,    21,     8,    64,    27,    36,     8,  2136,     8,     8,
      21,    34,    21,    36,    15,    21,     8,     8,  1011,    63,
      15,    21,    21,   124,    68,  1367,  1368,  1699,  1370,    21,
      21,    92,  1704,    64,   961,   962,  1378,    15,  1380,     8,
    1382,    64,     8,  1385,    15,  1717,    90,    91,   242,     7,
    1563,    15,    21,  2375,  2376,    21,    15,  1050,  2281,  2282,
       5,    92,   836,   837,     9,    15,    15,  1739,   129,    92,
      15,    16,    17,  1745,  1416,    15,    15,  1749,    15,  1576,
      15,    15,    27,  1425,  1567,  1568,  1569,    15,   149,  1431,
      15,    36,     5,  1433,    15,   124,     9,    10,   129,  1441,
     144,    14,    15,    16,    17,   239,   129,     3,    15,   246,
     154,  1451,    15,  1453,    27,  1457,    21,   246,   149,    64,
      26,    34,     8,    36,     5,     7,   149,    15,   240,    10,
      15,    15,     8,    14,    15,    16,    17,    15,  1478,     8,
     201,    15,    15,   166,   149,  1642,    27,    92,   175,  1489,
       8,    64,  1492,    34,    15,    36,   200,     8,     8,    15,
    1502,     8,     8,    26,     7,    62,    15,  1507,     8,  1509,
     201,    15,     8,    21,   287,     8,    15,  2162,   201,    92,
     326,     8,     8,    64,   129,   213,    15,   231,     9,    64,
    1532,   129,     9,    21,     8,     8,     8,  1842,     8,    15,
     244,    67,    37,  1545,   149,    67,    15,    15,    15,    15,
      15,    92,    15,    15,     8,    26,   129,   129,     7,    15,
       7,   166,  1564,    21,    21,  1567,  1568,  1569,    21,     7,
      18,    26,    15,    37,     7,  1577,   149,     8,   432,  1911,
      15,  2226,    26,    15,  2229,  2230,     8,  2131,   129,     8,
      15,    21,  1924,  1914,    21,  1846,   201,  1929,    15,    15,
    1932,    15,    15,    15,     8,    15,    21,    15,   149,     8,
    1942,  1613,  1944,   467,  1946,    21,  1948,    15,     5,    15,
      15,    15,     9,   477,     5,   166,    15,    15,   201,    16,
      17,  1633,     7,  2278,    62,    22,    23,    21,    25,     8,
       8,    28,    29,    30,    31,    32,     8,     8,  1650,    15,
      37,    15,   255,     7,  2299,  2300,     7,    15,  1311,   239,
     201,   166,    21,    16,    21,     5,    15,    15,  2080,    15,
       8,   208,     7,    15,  1989,    15,    16,    17,    15,     7,
       5,  1683,  1684,    15,  1999,   246,   246,    27,   246,     8,
      21,   246,   246,    15,    21,     8,    36,  2342,     7,     7,
      21,    21,     8,    21,    15,     8,  1708,    21,    15,     5,
      26,     7,   173,    15,    10,   255,     8,     7,    14,    15,
      16,    17,    21,   208,    64,    18,   580,   581,   582,    15,
     584,    27,    15,     8,    15,    71,    15,   591,    34,    15,
      36,  2152,  2153,    15,    15,    45,    46,    21,    48,    49,
       8,   605,    92,    53,    21,    21,    21,    21,    21,    21,
      15,    61,     5,    15,  1417,     7,    66,    20,    64,    69,
       9,    21,    26,    21,    44,    21,    21,    77,    15,    79,
      21,    81,    15,    21,    18,    21,    26,     8,    15,   129,
      15,    26,     7,   647,    26,    21,    92,    15,    21,     8,
    1802,  1803,  1804,  1805,   104,    15,  1459,    21,   662,   149,
      21,    15,   254,  1815,     8,   115,    21,    87,  2226,     7,
    2228,     7,  1475,  1476,  1477,    21,  1479,  1480,  2133,    37,
    1483,   132,     7,   129,     7,   255,    21,   691,  1491,   139,
      21,    15,     7,  1845,   698,    15,    15,  1849,    15,   119,
     704,   705,   152,   149,    15,    15,    15,    15,    15,    15,
       8,   201,  1862,     7,    15,     8,    21,    21,     7,    21,
     170,     7,     7,   143,    15,   145,   176,    78,     8,    21,
       7,     7,    15,  1883,   184,    17,   186,    21,   188,     7,
     190,    15,  2224,    21,    17,   749,  1898,   197,     7,    15,
    1902,     7,  1904,   213,   128,   201,   864,  1217,   178,   872,
    1563,  1564,  1914,   183,   214,   215,  1900,   187,  1920,  1921,
    1153,   191,  1774,  1507,   194,  1059,   553,  1927,  1511,  2110,
    1775,   561,   232,  1248,   681,  1541,  1936,   901,  2115,   239,
    2011,   564,   901,  1802,  1794,  1991,   216,  1441,  1123,  1651,
    2062,  1898,  1425,   253,  1954,  2082,   256,  1921,   994,     5,
     230,  1015,  1362,     9,  1339,  1057,   236,   821,   822,  1624,
      16,    17,  1626,  1973,  1627,  1628,  1629,    23,    75,    25,
    1823,  2381,    28,    29,    30,    31,    32,  1848,  1841,   682,
     237,    37,   443,   237,  1347,   763,  1385,  1560,  2000,  1003,
    1040,  1563,  1071,   808,   966,   630,   237,  2009,   237,  2011,
    2012,  2013,  2014,  2015,  2016,  1142,   631,   633,   632,  2161,
    1364,  1366,     5,  2042,  2340,  1902,  2212,    10,   778,   984,
    2317,    14,    15,    16,    17,   982,  1056,  1009,  1845,  1422,
     996,  2262,  2225,  2043,    27,  1885,  2342,  2377,  2379,  2362,
    2169,    34,  1676,    36,  1439,   637,  1905,    40,   912,   913,
     914,   915,   916,   917,   918,   919,   920,   921,   922,   923,
     924,   925,   926,   927,   928,   929,   930,   484,  2080,  2081,
    2082,    64,  1851,   937,  1402,   733,    45,    46,   942,    48,
      49,   415,   396,  1909,    53,   949,  1489,   951,  2142,  1727,
    1746,  1702,    61,   363,  1707,  1750,  1740,    66,  1934,    92,
      69,  1933,   966,  2115,  2193,  1954,  1192,  1204,    77,   443,
      79,  1209,    81,  1212,    -1,    -1,   450,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   458,    -1,    -1,    -1,   992,    -1,
      -1,    -1,    -1,    -1,   998,   104,   129,    -1,    -1,    -1,
    2152,  2153,    -1,    -1,    -1,    -1,   115,    -1,    -1,  2161,
       5,  1015,    -1,    -1,    -1,    10,   149,    -1,    -1,    14,
      15,    16,    17,    -1,     5,    -1,    -1,    -1,    -1,    10,
     139,    -1,    27,    14,    15,    16,    17,    -1,  1841,    34,
      -1,    36,    -1,   152,    -1,  1848,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,    -1,
      -1,   170,    -1,    -1,  2216,    -1,    -1,   176,   201,    64,
      -1,    -1,    -1,    -1,  2226,   184,  2228,   186,    -1,   188,
      -1,   190,    -1,    64,    -1,    -1,   560,    -1,   197,    -1,
    2240,    -1,     5,    -1,    -1,  1099,     9,    92,    -1,  2251,
      -1,    -1,    -1,    16,    17,   214,   215,    -1,    -1,    22,
      23,    92,    25,    -1,  1118,    28,    29,    30,    31,    32,
      -1,    -1,    35,   232,    37,    38,    -1,    -1,    -1,    -1,
      -1,  2281,  2282,    -1,   129,    -1,    -1,  1141,  1142,    -1,
      -1,    -1,    -1,    -1,   253,    -1,    -1,   256,   129,    -1,
     624,     5,    -1,    -1,   149,    -1,    10,    -1,    -1,    -1,
      14,    15,    16,    17,    -1,  2317,     5,  2319,   149,    -1,
      -1,    10,    -1,    27,    -1,    14,    15,    16,    17,    -1,
      34,    -1,    36,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    15,    16,    17,    -1,    34,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,   201,    -1,    -1,    -1,
      64,    -1,    36,    -1,    -1,    -1,    -1,  2367,    -1,    -1,
     201,    -1,    -1,    -1,    -1,    64,    -1,  2377,    -1,  2379,
    2380,    -1,  2035,    -1,    -1,    -1,    -1,    -1,    92,  1243,
      64,    -1,  2392,   717,    -1,    44,    -1,    -1,    -1,     7,
      -1,  1255,    10,    92,    -1,    -1,    14,    15,    16,    17,
      -1,   735,    -1,    -1,    -1,    -1,    -1,    -1,    92,    27,
      -1,    -1,    -1,    -1,   748,   129,    34,    -1,    36,  1283,
      -1,    -1,   756,   757,    -1,    -1,    -1,   761,    87,    -1,
     129,  1295,    -1,    -1,    93,   149,    -1,    -1,    -1,  2102,
    2103,    -1,    -1,    -1,     7,   129,    64,    10,    -1,    -1,
     149,    14,    15,    16,    17,   789,    -1,    -1,    -1,    -1,
     119,    -1,    -1,   797,    27,   149,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    36,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1346,  1347,   143,    -1,   145,   201,    -1,    -1,
      10,   825,    -1,   827,    14,    15,    16,    17,  1362,    -1,
      -1,    64,   201,    -1,    -1,  1369,    -1,    27,    -1,    -1,
      -1,   129,   846,   847,    34,  1379,    36,   201,    -1,   178,
      -1,  1385,    -1,  1387,   183,    -1,    -1,    -1,   187,    92,
      -1,   149,   191,    -1,    -1,   194,  1400,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,   166,  1413,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   216,    78,    -1,
    1424,    -1,    -1,    -1,  2227,    -1,   129,    -1,    -1,    -1,
      -1,   230,    92,  1437,    -1,    -1,    -1,   236,  1442,    -1,
    1444,  2244,    -1,   201,    -1,    -1,   149,  2250,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   935,   936,    -1,    -1,    -1,    -1,    -1,    -1,   129,
      -1,    -1,    -1,    -1,    12,     7,    -1,    -1,    10,    -1,
      18,    -1,    14,    15,    16,    17,    -1,   961,   962,   149,
      28,    -1,    -1,    31,    -1,    27,    34,    -1,   201,    -1,
      -1,    -1,    34,    41,    36,    -1,    -1,    45,    -1,    -1,
      -1,    49,    -1,  1517,   988,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    64,    71,    72,    -1,    -1,  1011,    -1,    77,
      78,   201,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    -1,    91,  1558,  1559,  1560,    -1,    -1,    -1,
      92,    -1,   100,    -1,    -1,    -1,    -1,   105,    -1,   107,
      -1,    -1,    -1,   111,    -1,    -1,  1050,   115,    -1,   117,
    1584,    -1,    -1,    -1,    -1,    -1,   124,    -1,  1592,    -1,
     128,    -1,  1596,    -1,   132,    -1,   134,   129,    -1,    -1,
    1604,    -1,     7,   141,   142,    10,    -1,   145,   146,    14,
      15,    16,    17,   151,    -1,   153,    -1,   149,     7,   157,
      -1,    10,    27,    -1,    -1,    14,    15,    16,    17,    34,
      -1,    36,  1636,     7,  1638,    -1,    10,    -1,    27,    -1,
      14,    15,    16,    17,    -1,    34,   184,    36,   186,    -1,
      10,    -1,    -1,    27,    14,    15,    16,    17,    -1,    64,
      34,    -1,    36,    -1,    -1,    -1,  1140,    27,    -1,   201,
      -1,    -1,    -1,    -1,    34,    64,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    14,
      15,    16,    17,    92,    64,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    27,   592,    -1,     9,    -1,    -1,    92,    34,
      -1,    36,    16,    17,   129,    -1,    -1,    -1,    -1,    23,
      -1,    25,    92,    -1,    28,    29,    30,    31,    32,    -1,
     129,    -1,    -1,    37,   149,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,   129,    -1,    -1,    -1,    -1,
     149,    -1,    -1,    -1,  1768,  1769,    -1,    -1,    -1,   129,
      -1,    -1,  1776,  1247,     5,   149,     7,    92,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,   149,
      21,    22,    23,    24,    25,    -1,   201,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,   201,  1817,   129,    -1,    -1,    -1,    -1,  1823,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   201,    -1,    -1,
      -1,    -1,    -1,    -1,   149,    -1,    -1,  1311,    -1,    -1,
      -1,   201,    -1,    -1,    -1,    -1,    -1,   385,  1852,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1861,    -1,    -1,
      -1,    -1,    -1,   742,    -1,    -1,    -1,   746,    -1,    -1,
      -1,    -1,     5,    -1,  1878,  1879,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,   201,    -1,    -1,    22,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
      33,  1905,    35,    -1,    37,    38,  1380,    -1,  1382,  1913,
      -1,    -1,    -1,    -1,   793,    -1,    -1,    -1,  1922,    -1,
      -1,    -1,    -1,    -1,    -1,   804,    -1,  1401,  1402,    -1,
      -1,    -1,    -1,    -1,  1938,    -1,  1940,  1411,    -1,    -1,
      -1,    -1,    -1,  1417,    -1,  1419,    -1,    -1,  1422,    -1,
     488,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,
    1434,    -1,    16,    17,  1438,  1439,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    38,  1459,    -1,    -1,    -1,    -1,
      -1,    -1,  1466,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1475,  1476,  1477,    -1,  1479,  1480,    -1,    -1,  1483,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1491,    -1,  2023,
    1494,  1495,  1496,    -1,  2028,    -1,    -1,   906,    -1,   908,
     909,   910,   911,    -1,    -1,    -1,    -1,    -1,  2042,    -1,
      -1,    -1,  2046,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,  2056,    -1,    16,    17,    -1,  2061,  1532,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   967,    -1,
    1564,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2110,     5,    -1,    -1,
     989,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
     999,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,  2145,  1021,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1627,  1628,  1629,  2160,    -1,  1037,    -1,
       5,    -1,  1041,  1042,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1676,    -1,    -1,    -1,    -1,  2211,  2212,    -1,
      -1,  2215,    -1,  2217,    -1,    -1,    -1,    -1,    -1,  1098,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2233,
    2234,  2235,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2245,    -1,     5,    -1,     7,  2250,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,  2262,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,  1156,  1157,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2293,
    2294,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2305,    -1,    -1,  2308,    -1,  2310,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1789,  1790,  1791,  1792,  1793,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2340,    -1,    -1,    -1,
    2344,    -1,    -1,   881,  2348,  2349,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2360,  2361,  2362,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1841,    -1,    -1,
      -1,    -1,    -1,    -1,  1848,    -1,    -1,    -1,    -1,    -1,
    1259,  1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,  1268,
    1269,  1270,  1271,  1272,  1273,  1274,  1275,  1276,  1277,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1882,    -1,
      -1,    -1,    -1,    -1,  1293,    -1,    -1,    -1,    -1,    -1,
      -1,  1300,    -1,  1302,    -1,    -1,    -1,    -1,    -1,  1903,
      -1,    -1,    -1,  1312,    -1,    -1,    -1,    -1,    -1,    -1,
    1914,    -1,    -1,   981,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
    1934,    -1,  1341,    16,    17,    -1,  1345,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
       5,    -1,    -1,    -1,     9,    10,  2000,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,  1414,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,  1428,
      35,    -1,    37,    38,    -1,     5,    -1,    -1,  2032,     9,
      10,  2035,    -1,  2037,    -1,    -1,    16,    17,    -1,  1448,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,     5,    -1,    -1,    -1,     9,    10,  2102,  2103,
      -1,    -1,    -1,    16,    17,    -1,    -1,  1516,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1549,    -1,    -1,    -1,    -1,    -1,    -1,  1556,    -1,    -1,
      -1,    -1,    -1,  1562,    -1,    -1,  1224,    -1,  2162,    -1,
      -1,    -1,  2166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,  1588,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,  1601,    -1,    28,    29,    30,    31,    32,    33,
    1609,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
    1619,    -1,    -1,  1622,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2226,  2227,  2228,  2229,  2230,    -1,  1637,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1648,
    2244,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,  1662,    -1,    -1,     9,    10,    -1,  1668,
      -1,    -1,    -1,    16,    17,  1674,    -1,    -1,    21,    22,
      23,    24,    25,    -1,  2278,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,     5,    -1,    -1,    -1,
       9,    10,    -1,    -1,    -1,  2299,  2300,    16,    17,  2303,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,  2342,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,     5,    -1,    -1,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,  1780,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,  1824,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,     5,    -1,    -1,  1844,     9,    10,  1847,    -1,
      -1,  1850,    -1,    16,    17,  1854,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,  1877,    -1,
       5,  1880,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,  1900,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,     8,     9,    10,    -1,
    1979,  1980,    -1,    -1,    16,    17,    -1,    -1,  1987,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,  2018,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,  2040,     5,    -1,    -1,  2044,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,  2054,  2055,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,  2085,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,  2095,  2096,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2125,    -1,  2127,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,     8,     9,
      10,    -1,  2141,    -1,    -1,  2144,    16,    17,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    -1,  2156,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
       5,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,  2221,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2255,    -1,  2257,    -1,
      -1,    -1,  2261,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2273,  2274,    -1,  2276,     5,    -1,
      -1,     8,     9,    10,    -1,    -1,    -1,  2286,  2287,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,     5,    -1,    -1,    -1,     9,    10,    -1,  2318,
      -1,  2320,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,  2332,  2333,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    14,    15,    16,    17,  2354,    19,    -1,    21,  2358,
      23,    24,    -1,    26,    -1,    -1,  2365,    30,    -1,    32,
      33,    -1,    -1,    36,    37,    38,    -1,    40,    -1,    42,
      43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    51,    52,
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
     183,    -1,   185,    -1,   187,    -1,   189,     5,   191,   192,
     193,     9,    10,     6,    -1,    -1,    -1,    -1,    16,    17,
      13,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    -1,    48,    49,    50,    51,    52,
      53,    -1,   245,    56,    57,   248,    -1,   250,    61,    62,
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
     313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   322,
     323,   324,   325,     5,   327,   328,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,     5,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,   569,   570,    22,    23,
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
       0,   332,     0,     1,   150,   257,   333,   334,   116,     6,
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
     311,   312,   313,   322,   323,   324,   325,   327,   328,   335,
     337,   340,   352,   353,   357,   358,   359,   365,   366,   367,
     368,   370,   371,   373,   375,   376,   377,   378,   385,   386,
     387,   388,   389,   390,   394,   395,   396,   400,   401,   439,
     441,   454,   497,   498,   500,   501,   507,   508,   509,   510,
     517,   518,   519,   520,   522,   525,   529,   530,   531,   532,
     533,   539,   540,   541,   552,   553,   554,   556,   559,   562,
     567,   568,   570,   572,   574,   577,   578,   602,   603,   614,
     615,   616,   617,   622,   625,   628,   631,   632,   680,   681,
     682,   683,   684,   685,   686,   687,   693,   695,   697,   699,
     701,   702,   703,   704,   705,   708,   710,   711,   712,   715,
     716,   720,   721,   723,   724,   725,   726,   727,   728,   731,
     736,   741,   742,   743,   744,   745,   762,   765,   766,   767,
     768,   774,   777,   782,   783,   784,   787,   788,   789,   790,
     791,   792,   793,   794,   795,   796,   797,   798,   799,   800,
     801,   806,   807,   808,   809,   810,   820,   821,   822,   823,
     824,   825,   826,   827,    15,   464,   464,   526,   526,   526,
     526,   526,   464,   526,   526,   336,   526,   526,   526,   464,
     526,   464,   526,   526,   464,   526,   526,   526,   463,   526,
     464,   526,   526,     7,    15,   465,    15,   464,   585,   526,
     464,   349,   526,   526,   526,   526,   526,   526,   526,   526,
     526,   526,   129,   342,   506,   506,   526,   526,   526,   464,
     526,   342,   526,   464,   464,   526,   526,   463,   336,   464,
     464,    64,   348,   526,   526,   464,   464,   464,   464,   464,
     464,   464,   526,   403,   526,   526,   526,   342,   440,   336,
     464,   526,   526,   526,   464,   526,   464,   526,   526,   464,
     526,   526,   526,   464,   336,   464,   349,   526,   526,   349,
     526,   464,   526,   526,   526,   464,   526,   526,   464,   526,
     464,   526,   526,   526,   526,   526,   526,    15,   464,   563,
     464,   336,   464,   464,   526,   526,   526,    15,     8,   464,
     464,   526,   526,   526,   464,   526,   526,   526,   526,   526,
     526,   526,   526,   526,   526,   526,   526,   526,   526,   526,
     526,   526,   526,   526,   526,   526,   526,   526,   526,   526,
     526,   464,   526,   464,   526,   526,   526,   526,   526,    15,
      15,    15,   342,   839,   257,   551,   124,   233,   373,    15,
     345,   551,     8,     8,     8,     8,     7,     8,   124,   337,
     360,     8,   342,   374,     8,     8,     8,     8,     8,   521,
       8,   521,     8,     8,     8,     8,   521,   551,     7,   218,
     252,   498,   500,   509,   510,   239,   518,   518,    10,    14,
      15,    16,    17,    27,    34,    36,    64,    92,   149,   201,
     342,   354,   470,   471,   473,   474,   475,   476,   482,   483,
     484,   485,   486,   489,    15,   526,     5,     9,    15,    16,
      17,   129,   472,   474,   482,   535,   549,   550,   526,    15,
     535,   526,     5,   534,   535,   550,   535,     8,     8,     8,
       8,     8,     8,     8,     8,     7,     8,     8,     5,     7,
     342,   612,   613,   342,   605,   465,    15,    15,   149,   453,
     342,   342,   713,   714,     8,   342,   629,   630,   714,   342,
     344,   342,    15,   502,   547,    23,    37,   342,   392,   393,
      15,   342,   575,   342,   644,   644,   342,   626,   627,   342,
     505,   402,    15,     8,   342,   555,   149,   719,   505,     7,
     448,   449,   464,   586,   587,   342,   581,   587,    15,   527,
     342,   557,   558,   505,    15,    15,   505,   719,   506,   505,
     505,   505,   505,   342,   505,   345,   505,    15,   397,   465,
     473,   474,    15,   339,   342,   342,   623,   624,   455,   456,
     457,   458,     8,   645,   709,    15,   342,   569,   342,   560,
     561,    15,    15,   342,   465,    15,   470,   722,    15,    15,
     342,   696,   698,     8,   342,    37,   391,    15,   474,   475,
     465,    15,    15,   527,   453,   465,   474,   342,   688,     5,
      15,   549,   550,   465,   342,   343,   465,   548,    15,   473,
     606,   607,   581,   585,   342,   573,   342,   668,   668,    15,
     342,   571,   688,   470,   481,   465,   349,    15,   342,   674,
     674,   674,   674,   674,   470,   564,   565,   342,   566,   465,
     338,   342,   465,   342,   694,   696,   342,   464,   465,   342,
     442,    15,    15,   548,   342,    15,   587,    15,   587,   587,
     587,   587,   748,   804,   587,   587,   587,   587,   587,   587,
     748,   342,   349,   811,   812,   813,    15,    15,    15,   349,
     828,   829,   830,   831,   349,   832,   833,   834,   835,   836,
     349,   837,   838,   336,   336,   124,     5,    21,   342,   346,
     347,   341,   349,   342,   342,   342,   393,     7,   349,   336,
     124,   342,   342,     5,    15,   380,   381,   342,   393,   393,
     393,   393,   392,   473,   391,   342,   342,   397,   404,   405,
     407,   408,   526,   526,   239,   383,   470,   471,   470,   470,
     470,   470,     5,     9,    16,    17,    22,    23,    24,    25,
      26,    28,    29,    30,    31,    32,    33,    35,    37,    38,
     354,    15,   246,     3,    15,   246,   246,    15,   479,   480,
      21,   523,   547,   481,     5,     9,   166,   536,   537,   538,
     549,    26,   549,     5,     9,    23,    37,   472,   548,   549,
     548,     8,    15,   474,   542,   543,    15,   470,   471,   486,
     544,   545,   546,   544,   555,   342,   569,   571,   573,   575,
     342,     7,   349,   694,     8,    21,   607,   393,   495,   470,
     240,   521,    15,   349,    15,   447,     8,   547,     7,   470,
     503,   504,   505,    15,   342,   447,   393,   452,   453,     8,
     404,   495,   349,   447,    15,     8,    21,     5,     7,   450,
     451,   470,   342,     8,    21,     5,    58,    86,   126,   137,
     165,   258,   588,   584,   585,   175,   576,   470,   149,   516,
       8,   470,   470,   341,   342,   398,   399,   473,   478,   342,
      26,   342,   511,   512,   514,   345,     8,     8,    15,   231,
     373,   459,   349,     8,   709,   342,   473,   678,   688,   706,
     707,     8,    26,     5,     9,    16,    17,    22,    23,    24,
      25,    28,    29,    30,    31,    32,    33,    34,    35,    37,
      38,   354,   355,   356,   342,   349,   363,   473,   470,    15,
     349,   342,   342,   473,   473,   496,     8,   645,   700,   342,
     473,   633,   634,   342,   437,   438,   516,   393,    18,   548,
     549,   548,   369,   372,   612,   607,     7,   585,   587,   678,
     688,   689,   690,   392,   393,   431,   432,    62,   473,   732,
      15,     7,     8,    21,   563,   393,   345,   393,   447,     8,
     643,   665,    21,   349,   342,     8,   470,   470,   447,   473,
     521,   769,   473,   287,   781,   781,   521,   778,   781,    15,
     521,   746,   521,   785,   746,   746,   521,   763,   521,   775,
     447,   147,   148,   180,   314,   315,   318,   319,   350,   814,
     815,   816,     8,    21,   474,   649,   817,    21,   817,   349,
     729,   730,   191,   208,     8,    21,    41,   209,   228,     8,
      21,   326,     8,    21,   342,   338,   336,     8,    21,   213,
     350,   447,    44,    87,    93,   119,   143,   145,   178,   183,
     187,   191,   194,   216,   230,   236,   361,   362,   364,   342,
     336,   464,   527,   547,   374,   447,   521,   521,     8,    37,
      15,   342,   410,   415,   349,    15,   490,    21,     8,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   547,    64,
     129,   466,   468,   547,   473,   484,   487,    64,   487,   481,
       8,    21,     5,   470,   524,   538,     8,    21,     5,     9,
     470,    21,   470,   549,   549,   549,   549,   549,    21,   542,
     542,     8,   470,   471,   545,   546,     8,     8,     8,   447,
     447,   464,    43,    82,    87,    88,    94,   228,   259,   303,
     616,   613,   349,   473,   476,   477,   493,    21,   342,    15,
     469,   470,    67,   448,   630,   470,     7,     8,    21,   523,
      37,     8,    21,   627,   473,   476,   492,   494,    67,   547,
     717,   450,     7,   447,   587,    15,    15,    15,    15,    15,
      15,   576,   587,   342,    21,   528,   558,    21,    21,    15,
       8,    21,     8,   480,   474,     8,   513,    26,   341,   624,
     456,   129,   460,   461,   462,   378,   169,   208,   282,   349,
      15,     7,     8,    21,   561,    21,    21,   147,   148,   180,
      21,    18,    21,     7,   470,   488,   175,   321,    37,     8,
      21,   349,     8,    21,    26,     8,    21,   528,   470,    21,
     433,   434,   433,    21,     7,   587,   576,    15,     7,     8,
      21,     8,    15,    15,    26,   675,   676,   678,   470,   565,
     349,     8,   665,     8,   643,   374,   364,   351,    21,    21,
      21,   587,   521,    21,   587,   521,   805,   587,   521,   587,
     521,   587,   521,   587,   521,    15,    15,    15,    15,    15,
      15,   349,   813,     8,    21,    21,   182,   315,   318,     8,
      21,    15,    15,   829,    15,    15,    15,   833,   838,   345,
     342,   347,    15,   379,   380,   447,   464,    15,     7,     8,
     342,   447,    15,   484,     5,   382,   470,   538,   393,   473,
     407,    15,    16,    17,    27,    36,    59,    64,    92,   149,
     201,   406,   408,   418,   419,   420,   421,   422,   423,   424,
     425,   410,   415,   416,   417,    15,   411,   412,    62,   470,
     544,   471,   466,    21,     8,   467,   470,   488,   538,     7,
     547,   453,   470,   547,     8,   543,    21,     8,     8,     8,
     471,   546,   471,   546,   471,   546,   342,   255,    15,    15,
       8,    21,   453,   452,     8,    21,     7,    21,   470,   503,
      21,   453,   521,     8,    21,     7,   538,   718,     8,    21,
     451,   470,   588,   547,    15,   590,   342,   589,   589,   470,
     589,   447,   587,   239,   505,   469,   399,   399,   342,   470,
     512,    21,   470,   488,     8,    21,    16,    15,    15,    15,
     469,   706,   707,   465,   473,   737,     7,   470,     7,    21,
      21,   342,   583,   474,   473,   634,   587,   635,   470,   438,
     521,     8,    47,   177,   342,   436,   349,   604,   606,   576,
       7,     7,   470,   691,   692,   689,   690,   432,   470,     5,
     590,   733,   734,   740,   470,   600,     8,    21,    15,    71,
     208,   349,   349,   465,   172,   342,   445,   446,   474,   191,
     208,   282,   285,   290,   298,   749,   750,   751,   758,   770,
     771,   772,   587,   266,   779,   780,   781,   587,    37,   473,
     802,   803,    84,   265,   289,   299,   304,   747,   749,   750,
     751,   752,   753,   754,   756,   757,   758,   587,   749,   750,
     751,   752,   753,   754,   756,   757,   758,   771,   772,   786,
     587,   749,   750,   751,   758,   764,   587,   749,   750,   776,
     587,   817,   817,   817,   349,   818,   819,   817,   817,   474,
     730,   649,   349,   669,   675,   689,   675,   342,    18,    26,
     384,    15,   363,     7,   349,   379,   528,   528,   383,     5,
     470,   421,   422,   423,   426,   422,   424,   422,   424,   246,
     246,   246,   246,   246,     8,    37,   342,   409,   473,     5,
     411,   412,     8,    15,    16,    17,   149,   342,   409,   413,
     414,   427,   428,   429,   430,    15,   412,    15,    21,   491,
      21,    21,   480,   547,   470,   481,   524,   537,   549,   514,
     515,   471,   515,   515,   515,   447,   342,   608,   611,   547,
     466,   547,     8,    21,   470,     7,   383,   470,   547,     7,
     470,   547,   538,   601,   470,   591,   592,    21,    21,    21,
      21,     8,     8,   254,   499,   505,    21,   461,   462,   649,
     649,   649,    21,    21,   342,    15,    21,   470,     7,     7,
     470,   447,   173,     8,   639,   640,   641,   642,   643,   645,
     646,   647,   650,   651,   652,   665,   673,   514,   434,    15,
      15,   435,   255,     8,     7,     8,    21,    21,    21,     8,
      21,    21,   676,   677,    15,    15,   342,   342,   443,   444,
      18,     8,    26,   748,    15,   748,   748,    15,   587,   770,
     748,   587,   779,   342,     8,    21,    15,   748,    15,   748,
      15,   587,   747,   587,   786,   587,   764,   587,   776,    21,
      21,    21,   316,   317,     8,    21,    21,    21,    21,    22,
      24,    33,    35,   158,   159,   161,   162,   192,   234,   247,
     670,   671,   672,     8,    21,    21,    21,    21,    21,   470,
     470,   618,   619,    21,   362,   384,     5,   470,   374,     8,
      21,     8,   487,   487,   487,   487,   487,   418,     5,    15,
     408,   419,   412,   342,   409,   417,   427,   428,   428,     8,
      21,     7,    16,    17,     5,    37,     9,   427,   470,    20,
     480,   467,    21,    26,    21,    21,    21,    21,    15,   466,
      21,   477,   538,   453,   629,   465,   492,   538,   555,   718,
     470,    21,     8,    21,   470,   349,    15,    21,    21,    21,
       7,   738,   739,   740,   470,   470,     7,   473,   636,   349,
     641,    26,   436,    26,   355,   608,   606,   342,   579,   580,
     581,   582,   692,   734,   587,    78,   564,   342,   644,   689,
     666,    18,     8,   342,   446,   470,   587,   759,   349,   587,
     587,   804,   473,   802,   349,   470,   470,   587,   587,   587,
     587,   819,    15,    15,   349,     8,    21,     7,    21,    21,
     547,   426,   419,   547,   409,    26,    21,   427,   414,   428,
     428,   429,   429,   429,    21,   470,     5,   470,   488,   609,
     610,    21,   473,     8,   649,   473,     8,   592,   349,    21,
     254,   470,     8,    21,   470,    15,    41,   135,   191,   209,
     221,   223,   224,   226,   229,   320,   470,   435,    21,    21,
      15,     8,   132,   735,    21,    21,     7,    21,   668,   670,
     342,   444,     5,    16,    17,    22,    24,    33,    35,    37,
     159,   162,   247,   305,   306,   307,   761,    21,    94,   230,
     284,   295,   773,    37,   191,   288,   299,   755,    21,    21,
     474,   649,   670,     7,     7,   382,    21,   466,   413,   427,
      21,     8,     8,    21,   453,   538,   255,    15,    21,   739,
       5,   470,   637,   638,    15,   653,    15,    15,    15,    15,
      15,   674,   674,    15,    15,     8,   469,   580,   678,   679,
      15,   689,   667,   667,     7,     8,    21,   805,    21,    21,
       8,     7,   383,    21,    21,   470,   610,   470,   342,   593,
     594,   470,     8,    21,   587,   653,   688,   706,   649,   688,
     689,   678,   675,   470,   470,   648,   470,    21,     8,   349,
      21,     7,     8,    21,   649,   760,   470,   470,   474,   342,
     620,   621,    21,     8,    15,    21,   638,   148,   180,   654,
       7,    21,    21,     7,    21,    15,    21,    21,     8,    21,
       8,   678,    78,   669,   669,    21,    21,     8,   470,    40,
     470,   595,   596,   740,     7,     7,   655,   656,   678,   706,
     689,   564,   470,   470,    21,    21,    21,   621,   342,   597,
       8,    21,     8,    21,    15,    21,    21,    21,     8,    17,
     598,   599,   596,   656,   470,   657,   658,    21,   470,   600,
      17,     7,     8,    21,   600,   470,   658,    15,   349,   659,
     660,   661,   662,   663,   128,   157,   217,     8,    21,     7,
       7,    15,   664,   664,   664,   660,   349,   662,   663,   349,
     663,   468,     7,    21,   663
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
#line 756 "gram1.y"
    { (yyval.bf_node) = BFNULL; ;}
    break;

  case 3:
#line 758 "gram1.y"
    { (yyval.bf_node) = set_stat_list((yyvsp[(1) - (3)].bf_node),(yyvsp[(2) - (3)].bf_node)); ;}
    break;

  case 4:
#line 762 "gram1.y"
    { lastwasbranch = NO;  (yyval.bf_node) = BFNULL; ;}
    break;

  case 5:
#line 764 "gram1.y"
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
#line 778 "gram1.y"
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
#line 809 "gram1.y"
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
#line 818 "gram1.y"
    {
	      err("Unclassifiable statement", 10);
	      flline();
	      (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 9:
#line 824 "gram1.y"
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
#line 844 "gram1.y"
    { 
	      flline();	 needkwd = NO;	inioctl = NO;
/*!!!*/
              opt_kwd_ = NO; intonly = NO; opt_kwd_hedr = NO; opt_kwd_r = NO; as_op_kwd_= NO; optcorner = NO;
	      yyerrok; yyclearin;  (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 11:
#line 853 "gram1.y"
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
#line 869 "gram1.y"
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
#line 881 "gram1.y"
    {  PTR_BFND q = BFNULL;

	      (yyvsp[(3) - (3)].symbol)->variant = PROCEDURE_NAME;
	      (yyvsp[(3) - (3)].symbol)->decl = YES;   /* variable declaration has been seen. */
	      q = get_bfnd(fi,BLOCK_DATA, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
	      set_blobs(q, global_bfnd, NEW_GROUP1);
              add_scope_level(q, NO);
	    ;}
    break;

  case 14:
#line 891 "gram1.y"
    { 
              install_param_list((yyvsp[(3) - (4)].symbol), (yyvsp[(4) - (4)].symbol), LLNULL, PROCEDURE_NAME); 
	      /* if there is only a control end the control parent is not set */
              
	     ;}
    break;

  case 15:
#line 898 "gram1.y"
    { install_param_list((yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].symbol), LLNULL, PROCEDURE_NAME); 
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP) 
                   (yyvsp[(4) - (5)].symbol)->attr = (yyvsp[(4) - (5)].symbol)->attr | RECURSIVE_BIT;
              pred_bfnd->entry.Template.ll_ptr3 = (yyvsp[(1) - (5)].ll_node);
            ;}
    break;

  case 16:
#line 904 "gram1.y"
    {
              install_param_list((yyvsp[(3) - (5)].symbol), (yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].ll_node), FUNCTION_NAME);  
  	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(5) - (5)].ll_node);
            ;}
    break;

  case 17:
#line 909 "gram1.y"
    {
              install_param_list((yyvsp[(1) - (3)].symbol), (yyvsp[(2) - (3)].symbol), (yyvsp[(3) - (3)].ll_node), FUNCTION_NAME); 
	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
	    ;}
    break;

  case 18:
#line 914 "gram1.y"
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
#line 938 "gram1.y"
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
#line 964 "gram1.y"
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
#line 979 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, RECURSIVE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 22:
#line 981 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PURE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 23:
#line 983 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, ELEMENTAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 24:
#line 987 "gram1.y"
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
#line 1004 "gram1.y"
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
#line 1018 "gram1.y"
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
#line 1042 "gram1.y"
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
#line 1058 "gram1.y"
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
#line 1072 "gram1.y"
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
#line 1090 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 31:
#line 1092 "gram1.y"
    { PTR_SYMB s;
              s = make_scalar((yyvsp[(4) - (5)].hash_entry), TYNULL, LOCAL);
              (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 32:
#line 1099 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 33:
#line 1102 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_MAIN")); ;}
    break;

  case 34:
#line 1104 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry));
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
            ;}
    break;

  case 35:
#line 1110 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_BLOCK")); ;}
    break;

  case 36:
#line 1112 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry)); 
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
	    ;}
    break;

  case 37:
#line 1119 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 38:
#line 1121 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 39:
#line 1123 "gram1.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); ;}
    break;

  case 41:
#line 1128 "gram1.y"
    { (yyval.symbol) = set_id_list((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); ;}
    break;

  case 42:
#line 1132 "gram1.y"
    {
	      (yyval.symbol) = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, IO);
            ;}
    break;

  case 43:
#line 1136 "gram1.y"
    { (yyval.symbol) = make_scalar(look_up_sym("*"), TYNULL, IO); ;}
    break;

  case 44:
#line 1142 "gram1.y"
    { char *s;

	      s = copyn(yyleng+1, yytext);
	      s[yyleng] = '\0';
	      (yyval.charp) = s;
	    ;}
    break;

  case 45:
#line 1151 "gram1.y"
    { needkwd = 1; ;}
    break;

  case 46:
#line 1155 "gram1.y"
    { needkwd = NO; ;}
    break;

  case 47:
#line 1160 "gram1.y"
    { colon_flag = YES; ;}
    break;

  case 61:
#line 1181 "gram1.y"
    {
	      saveall = YES;
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 62:
#line 1186 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, (yyvsp[(4) - (4)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 63:
#line 1191 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL, SMNULL);
	      p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,FORMAT_STAT, SMNULL, p, LLNULL, LLNULL);
             ;}
    break;

  case 64:
#line 1198 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,PARAM_DECL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 77:
#line 1214 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, SMNULL, LLNULL, LLNULL, LLNULL); 
             /* add_scope_level($$, NO); */    
            ;}
    break;

  case 78:
#line 1218 "gram1.y"
    { PTR_SYMB s;

	      s = make_procedure((yyvsp[(3) - (3)].hash_entry), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 79:
#line 1226 "gram1.y"
    { PTR_SYMB s;

	      s = make_function((yyvsp[(4) - (5)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_OPERATOR, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 80:
#line 1234 "gram1.y"
    { PTR_SYMB s;


	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_ASSIGNMENT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 81:
#line 1243 "gram1.y"
    { parstate = INDCL;
              (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      /*process_interface($$);*/ /*podd 01.02.03*/
              /*delete_beyond_scope_level(pred_bfnd);*/
	    ;}
    break;

  case 82:
#line 1251 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 83:
#line 1255 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 84:
#line 1257 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 85:
#line 1261 "gram1.y"
    { (yyval.hash_entry) = look_up_op(PLUS); ;}
    break;

  case 86:
#line 1263 "gram1.y"
    { (yyval.hash_entry) = look_up_op(MINUS); ;}
    break;

  case 87:
#line 1265 "gram1.y"
    { (yyval.hash_entry) = look_up_op(ASTER); ;}
    break;

  case 88:
#line 1267 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DASTER); ;}
    break;

  case 89:
#line 1269 "gram1.y"
    { (yyval.hash_entry) = look_up_op(SLASH); ;}
    break;

  case 90:
#line 1271 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DSLASH); ;}
    break;

  case 91:
#line 1273 "gram1.y"
    { (yyval.hash_entry) = look_up_op(AND); ;}
    break;

  case 92:
#line 1275 "gram1.y"
    { (yyval.hash_entry) = look_up_op(OR); ;}
    break;

  case 93:
#line 1277 "gram1.y"
    { (yyval.hash_entry) = look_up_op(XOR); ;}
    break;

  case 94:
#line 1279 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NOT); ;}
    break;

  case 95:
#line 1281 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQ); ;}
    break;

  case 96:
#line 1283 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NE); ;}
    break;

  case 97:
#line 1285 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GT); ;}
    break;

  case 98:
#line 1287 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GE); ;}
    break;

  case 99:
#line 1289 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LT); ;}
    break;

  case 100:
#line 1291 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LE); ;}
    break;

  case 101:
#line 1293 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NEQV); ;}
    break;

  case 102:
#line 1295 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQV); ;}
    break;

  case 103:
#line 1300 "gram1.y"
    {
             PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, LLNULL, LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 104:
#line 1309 "gram1.y"
    { PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, (yyvsp[(5) - (7)].ll_node), LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 105:
#line 1319 "gram1.y"
    {
	     (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);
           ;}
    break;

  case 106:
#line 1327 "gram1.y"
    {
             (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);	
           ;}
    break;

  case 107:
#line 1337 "gram1.y"
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
#line 1358 "gram1.y"
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
#line 1377 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 110:
#line 1379 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 111:
#line 1381 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node); ;}
    break;

  case 112:
#line 1385 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 113:
#line 1387 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); ;}
    break;

  case 114:
#line 1391 "gram1.y"
    { type_options = type_options | PARAMETER_BIT; 
              (yyval.ll_node) = make_llnd(fi, PARAMETER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 115:
#line 1395 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 116:
#line 1397 "gram1.y"
    { type_options = type_options | ALLOCATABLE_BIT;
              (yyval.ll_node) = make_llnd(fi, ALLOCATABLE_OP, LLNULL, LLNULL, SMNULL);
	    ;}
    break;

  case 117:
#line 1401 "gram1.y"
    { type_options = type_options | DIMENSION_BIT;
	      attr_ndim = ndim;
	      attr_dims = (yyvsp[(2) - (2)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DIMENSION_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 118:
#line 1407 "gram1.y"
    { type_options = type_options | EXTERNAL_BIT;
              (yyval.ll_node) = make_llnd(fi, EXTERNAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 119:
#line 1411 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node); ;}
    break;

  case 120:
#line 1413 "gram1.y"
    { type_options = type_options | INTRINSIC_BIT;
              (yyval.ll_node) = make_llnd(fi, INTRINSIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 121:
#line 1417 "gram1.y"
    { type_options = type_options | OPTIONAL_BIT;
              (yyval.ll_node) = make_llnd(fi, OPTIONAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 122:
#line 1421 "gram1.y"
    { type_options = type_options | POINTER_BIT;
              (yyval.ll_node) = make_llnd(fi, POINTER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 123:
#line 1425 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, SAVE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 124:
#line 1429 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, STATIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 125:
#line 1433 "gram1.y"
    { type_options = type_options | TARGET_BIT; 
              (yyval.ll_node) = make_llnd(fi, TARGET_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 126:
#line 1439 "gram1.y"
    { type_options = type_options | IN_BIT;  type_opt = IN_BIT; 
              (yyval.ll_node) = make_llnd(fi, IN_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 127:
#line 1443 "gram1.y"
    { type_options = type_options | OUT_BIT;  type_opt = OUT_BIT; 
              (yyval.ll_node) = make_llnd(fi, OUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 128:
#line 1447 "gram1.y"
    { type_options = type_options | INOUT_BIT;  type_opt = INOUT_BIT;
              (yyval.ll_node) = make_llnd(fi, INOUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 129:
#line 1453 "gram1.y"
    { type_options = type_options | PUBLIC_BIT; 
              type_opt = PUBLIC_BIT;
              (yyval.ll_node) = make_llnd(fi, PUBLIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 130:
#line 1458 "gram1.y"
    { type_options =  type_options | PRIVATE_BIT;
               type_opt = PRIVATE_BIT;
              (yyval.ll_node) = make_llnd(fi, PRIVATE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 131:
#line 1465 "gram1.y"
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
#line 1476 "gram1.y"
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
#line 1489 "gram1.y"
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
#line 1500 "gram1.y"
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
#line 1513 "gram1.y"
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
#line 1523 "gram1.y"
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
#line 1536 "gram1.y"
    {
	      privateall = 1;
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 138:
#line 1541 "gram1.y"
    {
	      /*type_options = type_options | PRIVATE_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 139:
#line 1547 "gram1.y"
    {type_opt = PRIVATE_BIT;;}
    break;

  case 140:
#line 1551 "gram1.y"
    { 
	      (yyval.bf_node) = get_bfnd(fi, SEQUENCE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
            ;}
    break;

  case 141:
#line 1556 "gram1.y"
    {
	      /*saveall = YES;*/ /*14.03.03*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 142:
#line 1561 "gram1.y"
    {
	      /*type_options = type_options | PUBLIC_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 143:
#line 1567 "gram1.y"
    {type_opt = PUBLIC_BIT;;}
    break;

  case 144:
#line 1571 "gram1.y"
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
#line 1581 "gram1.y"
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
#line 1594 "gram1.y"
    {opt_kwd_hedr = YES;;}
    break;

  case 147:
#line 1599 "gram1.y"
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
#line 1618 "gram1.y"
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
#line 1644 "gram1.y"
    { (yyval.token) = ATT_GLOBAL; ;}
    break;

  case 150:
#line 1646 "gram1.y"
    { (yyval.token) = ATT_CLUSTER; ;}
    break;

  case 151:
#line 1658 "gram1.y"
    {
/*		  varleng = ($1<0 || $1==TYLONG ? 0 : typesize[$1]); */
		  vartype = (yyvsp[(1) - (1)].data_type);
		;}
    break;

  case 152:
#line 1665 "gram1.y"
    { (yyval.data_type) = global_int; ;}
    break;

  case 153:
#line 1666 "gram1.y"
    { (yyval.data_type) = global_float; ;}
    break;

  case 154:
#line 1667 "gram1.y"
    { (yyval.data_type) = global_complex; ;}
    break;

  case 155:
#line 1668 "gram1.y"
    { (yyval.data_type) = global_double; ;}
    break;

  case 156:
#line 1669 "gram1.y"
    { (yyval.data_type) = global_dcomplex; ;}
    break;

  case 157:
#line 1670 "gram1.y"
    { (yyval.data_type) = global_bool; ;}
    break;

  case 158:
#line 1671 "gram1.y"
    { (yyval.data_type) = global_string; ;}
    break;

  case 159:
#line 1676 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 160:
#line 1678 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 161:
#line 1682 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(3) - (5)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 162:
#line 1684 "gram1.y"
    { PTR_LLND l;

                 l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL); 
                 l->entry.string_val = (char *)"*";
                 (yyval.ll_node) = make_llnd(fi, LEN_OP, l,l, SMNULL);
                ;}
    break;

  case 163:
#line 1691 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(5) - (6)].ll_node), (yyvsp[(5) - (6)].ll_node), SMNULL);;}
    break;

  case 164:
#line 1695 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 165:
#line 1697 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 166:
#line 1699 "gram1.y"
    { /*$$ = make_llnd(fi, PAREN_OP, $2, LLNULL, SMNULL);*/  (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node);  ;}
    break;

  case 167:
#line 1707 "gram1.y"
    { if((yyvsp[(7) - (9)].ll_node)->variant==LENGTH_OP && (yyvsp[(3) - (9)].ll_node)->variant==(yyvsp[(7) - (9)].ll_node)->variant)
                (yyvsp[(7) - (9)].ll_node)->variant=KIND_OP;
                (yyval.ll_node) = make_llnd(fi, CONS, (yyvsp[(3) - (9)].ll_node), (yyvsp[(7) - (9)].ll_node), SMNULL); 
            ;}
    break;

  case 168:
#line 1714 "gram1.y"
    { if(vartype->variant == T_STRING)
                (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
              else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
            ;}
    break;

  case 169:
#line 1720 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 170:
#line 1726 "gram1.y"
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
#line 1735 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 172:
#line 1743 "gram1.y"
    {endioctl();;}
    break;

  case 173:
#line 1756 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 174:
#line 1758 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node); ;}
    break;

  case 175:
#line 1761 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, POINTST_OP, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 176:
#line 1765 "gram1.y"
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
#line 1780 "gram1.y"
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
#line 1796 "gram1.y"
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
#line 1814 "gram1.y"
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
#line 1834 "gram1.y"
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
#line 1854 "gram1.y"
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
#line 1876 "gram1.y"
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
#line 1893 "gram1.y"
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
#line 1911 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 185:
#line 1918 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 186:
#line 1925 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(q, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 187:
#line 1932 "gram1.y"
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
#line 1945 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,NAMELIST_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 189:
#line 1952 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(r, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 190:
#line 1959 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(q, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 191:
#line 1970 "gram1.y"
    { (yyval.symbol) =  make_local_entity((yyvsp[(2) - (3)].hash_entry), NAMELIST_NAME,global_default,LOCAL); ;}
    break;

  case 192:
#line 1974 "gram1.y"
    { (yyval.symbol) = NULL; /*make_common(look_up_sym("*"));*/ ;}
    break;

  case 193:
#line 1976 "gram1.y"
    { (yyval.symbol) = make_common((yyvsp[(2) - (3)].hash_entry)); ;}
    break;

  case 194:
#line 1981 "gram1.y"
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
#line 1999 "gram1.y"
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
#line 2010 "gram1.y"
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
#line 2022 "gram1.y"
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
#line 2034 "gram1.y"
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
#line 2048 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,EQUI_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node),
			     LLNULL, LLNULL);
	    ;}
    break;

  case 200:
#line 2054 "gram1.y"
    { 
	      add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 201:
#line 2061 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EQUI_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
           ;}
    break;

  case 202:
#line 2067 "gram1.y"
    { PTR_LLND p;
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (3)].ll_node), p, SMNULL);
	    ;}
    break;

  case 203:
#line 2073 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 204:
#line 2081 "gram1.y"
    {  PTR_SYMB s;
           s=make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
           (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$=$1; $$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 205:
#line 2088 "gram1.y"
    {  PTR_SYMB s;
           s=make_array((yyvsp[(1) - (4)].hash_entry),TYNULL,LLNULL,0,LOCAL);
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 207:
#line 2107 "gram1.y"
    { PTR_LLND p;
              data_stat = NO;
	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL,
			    SMNULL);
              p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,DATA_DECL, SMNULL, p, LLNULL, LLNULL);
            ;}
    break;

  case 210:
#line 2121 "gram1.y"
    {data_stat = YES;;}
    break;

  case 211:
#line 2125 "gram1.y"
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
#line 2170 "gram1.y"
    {;;}
    break;

  case 223:
#line 2174 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);;}
    break;

  case 224:
#line 2178 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL); 
              (yyval.symbol)->attr = (yyval.symbol)->attr | DATA_BIT; 
            ;}
    break;

  case 225:
#line 2184 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_SUBS, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 226:
#line 2188 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_RANGE, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 227:
#line 2192 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 228:
#line 2194 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 229:
#line 2198 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 230:
#line 2200 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 231:
#line 2204 "gram1.y"
    {(yyval.ll_node)= make_llnd(fi, DATA_IMPL_DO, (yyvsp[(2) - (7)].ll_node), (yyvsp[(6) - (7)].ll_node), (yyvsp[(4) - (7)].symbol)); ;}
    break;

  case 232:
#line 2208 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 233:
#line 2210 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 234:
#line 2214 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 235:
#line 2216 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 236:
#line 2218 "gram1.y"
    {
              (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr2 = (yyvsp[(3) - (3)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); 
            ;}
    break;

  case 237:
#line 2223 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 251:
#line 2247 "gram1.y"
    {if((yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->variant != TYPE_NAME)
               errstr("Undefined type %s",(yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->ident,319); 
           ;}
    break;

  case 268:
#line 2292 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ICON_EXPR, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 269:
#line 2294 "gram1.y"
    {
              PTR_LLND p;

              p = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 270:
#line 2301 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 271:
#line 2308 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 272:
#line 2315 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 273:
#line 2324 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 274:
#line 2326 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 275:
#line 2328 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 276:
#line 2332 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 277:
#line 2334 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 278:
#line 2338 "gram1.y"
    {
              PTR_LLND p;

              p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
              p->entry.ival = atoi(yytext);
              p->type = global_int;
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 279:
#line 2347 "gram1.y"
    {
              PTR_LLND p;
 
              p = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 280:
#line 2354 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 281:
#line 2361 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 282:
#line 2363 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 283:
#line 2367 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
             (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
           ;}
    break;

  case 284:
#line 2371 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol)); 
            (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
          ;}
    break;

  case 285:
#line 2377 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 286:
#line 2379 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), EXPR_LIST); ;}
    break;

  case 287:
#line 2383 "gram1.y"
    { as_op_kwd_ = YES; ;}
    break;

  case 288:
#line 2387 "gram1.y"
    { as_op_kwd_ = NO; ;}
    break;

  case 289:
#line 2392 "gram1.y"
    { 
             PTR_SYMB s; 
             s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
	     (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 290:
#line 2399 "gram1.y"
    { PTR_SYMB s;
	      s = make_function((yyvsp[(3) - (4)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,OPERATOR_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 291:
#line 2406 "gram1.y"
    { PTR_SYMB s;
	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,ASSIGNMENT_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 292:
#line 2416 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 293:
#line 2418 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 294:
#line 2422 "gram1.y"
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
#line 2434 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, MODULE_PROC_STMT, SMNULL, (yyvsp[(2) - (2)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 296:
#line 2437 "gram1.y"
    { PTR_SYMB s;
 	      PTR_LLND q;

	      s = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	    ;}
    break;

  case 297:
#line 2446 "gram1.y"
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
#line 2459 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
              /*add_scope_level($3->entry.Template.func_hedr, YES);*/ /*17.06.01*/
              copy_module_scope((yyvsp[(3) - (3)].symbol),LLNULL); /*17.03.03*/
              colon_flag = NO;
            ;}
    break;

  case 299:
#line 2465 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), (yyvsp[(6) - (6)].ll_node), LLNULL, LLNULL); 
              /*add_scope_level(module_scope, YES); *//* 17.06.01*/
              copy_module_scope((yyvsp[(3) - (6)].symbol),(yyvsp[(6) - (6)].ll_node)); /*17.03.03 */
              colon_flag = NO;
            ;}
    break;

  case 300:
#line 2471 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, LLNULL, LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 301:
#line 2477 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, (yyvsp[(7) - (7)].ll_node), LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (7)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 302:
#line 2485 "gram1.y"
    {
              if ((yyvsp[(1) - (1)].hash_entry)->id_attr == SMNULL)
	         warn1("Unknown module %s", (yyvsp[(1) - (1)].hash_entry)->ident,308);
              (yyval.symbol) = make_global_entity((yyvsp[(1) - (1)].hash_entry), MODULE_NAME, global_default, NO);
	      module_scope = (yyval.symbol)->entry.Template.func_hedr;
           
            ;}
    break;

  case 303:
#line 2495 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 304:
#line 2497 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 305:
#line 2501 "gram1.y"
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
#line 2522 "gram1.y"
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
#line 2547 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 308:
#line 2549 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 309:
#line 2553 "gram1.y"
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
#line 2584 "gram1.y"
    { ndim = 0;	explicit_shape = 1; (yyval.ll_node) = LLNULL; ;}
    break;

  case 311:
#line 2586 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 312:
#line 2589 "gram1.y"
    { ndim = 0; explicit_shape = 1;;}
    break;

  case 313:
#line 2590 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
	    ;}
    break;

  case 314:
#line 2595 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 315:
#line 2599 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
	      ++ndim;
	    ;}
    break;

  case 316:
#line 2607 "gram1.y"
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
#line 2616 "gram1.y"
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
#line 2625 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      ++ndim;
	    ;}
    break;

  case 319:
#line 2635 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,STAR_RANGE, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
              explicit_shape = 0;
	    ;}
    break;

  case 321:
#line 2644 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 322:
#line 2646 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 323:
#line 2650 "gram1.y"
    {PTR_LABEL p;
	     p = make_label_node(fi,convci(yyleng, yytext));
	     p->scope = cur_scope();
	     (yyval.ll_node) = make_llnd_label(fi,LABEL_REF, p);
	  ;}
    break;

  case 324:
#line 2658 "gram1.y"
    { /*PTR_LLND l;*/

          /*   l = make_llnd(fi, EXPR_LIST, $3, LLNULL, SMNULL);*/
             (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
             redefine_func_arg_type();
           ;}
    break;

  case 325:
#line 2673 "gram1.y"
    { /*undeftype = YES;
	    setimpl(TYNULL, (int)'a', (int)'z'); FB COMMENTED---> NOT QUITE RIGHT BUT AVOID PB WITH COMMON*/
	    (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	  ;}
    break;

  case 326:
#line 2680 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 327:
#line 2682 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 328:
#line 2686 "gram1.y"
    { 

            (yyval.ll_node) = make_llnd(fi, IMPL_TYPE, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
            (yyval.ll_node)->type = vartype;
          ;}
    break;

  case 329:
#line 2701 "gram1.y"
    { implkwd = YES; ;}
    break;

  case 330:
#line 2702 "gram1.y"
    { vartype = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 331:
#line 2706 "gram1.y"
    { (yyval.data_type) = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 332:
#line 2708 "gram1.y"
    { (yyval.data_type) = (yyvsp[(1) - (1)].data_type);;}
    break;

  case 333:
#line 2720 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 334:
#line 2722 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 335:
#line 2726 "gram1.y"
    {
	      setimpl(vartype, (int)(yyvsp[(1) - (1)].charv), (int)(yyvsp[(1) - (1)].charv));
	      (yyval.ll_node) = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.cval = (yyvsp[(1) - (1)].charv);
	    ;}
    break;

  case 336:
#line 2732 "gram1.y"
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
#line 2744 "gram1.y"
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
#line 2755 "gram1.y"
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
#line 2772 "gram1.y"
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
#line 2810 "gram1.y"
    { (yyval.ll_node) = LLNULL; endioctl(); ;}
    break;

  case 343:
#line 2812 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);  endioctl();;}
    break;

  case 344:
#line 2816 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 345:
#line 2818 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 346:
#line 2820 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
	      l->type = (yyvsp[(2) - (2)].ll_node)->type;
              (yyval.ll_node) = l; 
	    ;}
    break;

  case 347:
#line 2831 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 348:
#line 2835 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 349:
#line 2841 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 350:
#line 2843 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 351:
#line 2847 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 352:
#line 2849 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 353:
#line 2851 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 354:
#line 2855 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 355:
#line 2857 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 356:
#line 2861 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 357:
#line 2863 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 358:
#line 2865 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 359:
#line 2867 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 360:
#line 2869 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 361:
#line 2871 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 362:
#line 2873 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(1) - (2)].hash_entry), (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 363:
#line 2875 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 364:
#line 2877 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 365:
#line 2879 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eq.", EQ_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 366:
#line 2881 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".gt.", GT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 367:
#line 2883 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".lt.", LT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 368:
#line 2885 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", GTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 369:
#line 2887 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", LTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 370:
#line 2889 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ne.", NOTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 371:
#line 2891 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eqv.", EQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 372:
#line 2893 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".neqv.", NEQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 373:
#line 2895 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".xor.", XOR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 374:
#line 2897 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".or.", OR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 375:
#line 2899 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".and.", AND_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 376:
#line 2901 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".not.", NOT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 377:
#line 2903 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("//", CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 378:
#line 2905 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(2) - (3)].hash_entry), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 379:
#line 2908 "gram1.y"
    { (yyval.token) = ADD_OP; ;}
    break;

  case 380:
#line 2909 "gram1.y"
    { (yyval.token) = SUBT_OP; ;}
    break;

  case 381:
#line 2921 "gram1.y"
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
#line 2995 "gram1.y"
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
#line 3007 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 384:
#line 3009 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 385:
#line 3013 "gram1.y"
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
#line 3144 "gram1.y"
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
#line 3194 "gram1.y"
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
#line 3238 "gram1.y"
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
#line 3280 "gram1.y"
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
#line 3338 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 391:
#line 3340 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 392:
#line 3342 "gram1.y"
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
#line 3382 "gram1.y"
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
#line 3424 "gram1.y"
    { 
	      if ((yyvsp[(1) - (2)].ll_node)->type->variant == T_STRING) {
                 (yyvsp[(1) - (2)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (2)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node); (yyval.ll_node)->type = global_string;
              }
              else errstr("can't subscript of %s", (yyvsp[(1) - (2)].ll_node)->entry.Template.symbol->ident,44);
            ;}
    break;

  case 395:
#line 3434 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 396:
#line 3436 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 397:
#line 3440 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 398:
#line 3444 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 399:
#line 3446 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 400:
#line 3450 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 401:
#line 3452 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 402:
#line 3458 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 403:
#line 3460 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 404:
#line 3466 "gram1.y"
    {
              if ((yyvsp[(2) - (2)].ll_node) != LLNULL)
		 (yyval.ll_node) = make_llnd(fi, ARRAY_OP, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); 
	      else 
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);
             ;}
    break;

  case 405:
#line 3476 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 1;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 406:
#line 3482 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 0;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 407:
#line 3489 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,FLOAT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_float;
	    ;}
    break;

  case 408:
#line 3495 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DOUBLE_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_double;
	    ;}
    break;

  case 409:
#line 3503 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.ival = atoi(yytext);
	      (yyval.ll_node)->type = global_int;
	    ;}
    break;

  case 410:
#line 3511 "gram1.y"
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
#line 3527 "gram1.y"
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
#line 3537 "gram1.y"
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
#line 3550 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,COMPLEX_VAL, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL);
	      (yyval.ll_node)->type = global_complex;
	    ;}
    break;

  case 414:
#line 3557 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 415:
#line 3559 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 416:
#line 3582 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 417:
#line 3584 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 418:
#line 3586 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),SMNULL),(yyvsp[(5) - (5)].ll_node),SMNULL); ;}
    break;

  case 419:
#line 3588 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (4)].ll_node),LLNULL,SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 420:
#line 3590 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (4)].ll_node),SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 421:
#line 3592 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 422:
#line 3594 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (2)].ll_node),SMNULL); ;}
    break;

  case 423:
#line 3596 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL); ;}
    break;

  case 424:
#line 3599 "gram1.y"
    {in_vec=YES;;}
    break;

  case 425:
#line 3599 "gram1.y"
    {in_vec=NO;;}
    break;

  case 426:
#line 3600 "gram1.y"
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
#line 3614 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 428:
#line 3616 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 429:
#line 3639 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 430:
#line 3641 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 431:
#line 3643 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                  endioctl();
                ;}
    break;

  case 432:
#line 3659 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 433:
#line 3661 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 434:
#line 3663 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
             endioctl();
           ;}
    break;

  case 435:
#line 3676 "gram1.y"
    {stat_alloc = LLNULL;;}
    break;

  case 436:
#line 3680 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 437:
#line 3682 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 438:
#line 3690 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 439:
#line 3692 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 440:
#line 3694 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 441:
#line 3696 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 442:
#line 3750 "gram1.y"
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
#line 3772 "gram1.y"
    {
              make_extend((yyvsp[(3) - (3)].symbol));
              (yyval.bf_node) = BFNULL; 
              /* delete_beyond_scope_level(pred_bfnd); */
             ;}
    break;

  case 444:
#line 3785 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	    bind(); 
	    delete_beyond_scope_level(pred_bfnd);
	    position = IN_OUTSIDE;
          ;}
    break;

  case 445:
#line 3794 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 446:
#line 3797 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 447:
#line 3847 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = LOGIF_NODE;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 448:
#line 3853 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 449:
#line 3858 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (3)].ll_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 450:
#line 3876 "gram1.y"
    { make_elseif((yyvsp[(4) - (7)].ll_node),(yyvsp[(7) - (7)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL;;}
    break;

  case 451:
#line 3878 "gram1.y"
    { make_else((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 452:
#line 3880 "gram1.y"
    { make_endif((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 453:
#line 3882 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 454:
#line 3884 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CONTAINS_STMT, SMNULL, LLNULL, LLNULL, LLNULL); ;}
    break;

  case 455:
#line 3887 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = FORALL_STAT;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 456:
#line 3893 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 457:
#line 3895 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node); (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 458:
#line 3897 "gram1.y"
    { make_endforall((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 459:
#line 3900 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 460:
#line 3902 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 461:
#line 3904 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 462:
#line 3931 "gram1.y"
    { 	     
	     /*  if($5 && $5->labdefined)
		 execerr("no backward DO loops", (char *)NULL); */
	       (yyval.bf_node) = make_do(WHILE_NODE, LBNULL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL);
	       /*$$->entry.Template.ll_ptr3 = $1;*/	     
           ;}
    break;

  case 463:
#line 3940 "gram1.y"
    {
               if( (yyvsp[(4) - (7)].label) && (yyvsp[(4) - (7)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(WHILE_NODE, (yyvsp[(4) - (7)].label), SMNULL, (yyvsp[(7) - (7)].ll_node), LLNULL, LLNULL);            
	    ;}
    break;

  case 464:
#line 3948 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 465:
#line 3950 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(5) - (6)].ll_node);;}
    break;

  case 466:
#line 3952 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 467:
#line 3957 "gram1.y"
    {  
               if( (yyvsp[(4) - (11)].label) && (yyvsp[(4) - (11)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (11)].label), (yyvsp[(7) - (11)].symbol), (yyvsp[(9) - (11)].ll_node), (yyvsp[(11) - (11)].ll_node), LLNULL);            
	    ;}
    break;

  case 468:
#line 3964 "gram1.y"
    {
               if( (yyvsp[(4) - (13)].label) && (yyvsp[(4) - (13)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (13)].label), (yyvsp[(7) - (13)].symbol), (yyvsp[(9) - (13)].ll_node), (yyvsp[(11) - (13)].ll_node), (yyvsp[(13) - (13)].ll_node));            
	    ;}
    break;

  case 469:
#line 3972 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CASE_NODE, (yyvsp[(4) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 470:
#line 3974 "gram1.y"
    { /*PTR_LLND p;*/
	     /* p = make_llnd(fi, DEFAULT, LLNULL, LLNULL, SMNULL); */
	      (yyval.bf_node) = get_bfnd(fi, DEFAULT_NODE, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 471:
#line 3978 "gram1.y"
    { make_endselect((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 472:
#line 3981 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(6) - (7)].ll_node), LLNULL, LLNULL) ; ;}
    break;

  case 473:
#line 3983 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(7) - (8)].ll_node), LLNULL, (yyvsp[(1) - (8)].ll_node)) ; ;}
    break;

  case 474:
#line 3987 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 475:
#line 3993 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 476:
#line 3995 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 477:
#line 3997 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 478:
#line 3999 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL); ;}
    break;

  case 479:
#line 4003 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 480:
#line 4005 "gram1.y"
    { PTR_LLND p;
	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 481:
#line 4013 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 482:
#line 4015 "gram1.y"
    { (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSTRUCT_NAME, global_default,
                                     LOCAL); ;}
    break;

  case 483:
#line 4021 "gram1.y"
    {(yyval.hash_entry) = HSNULL;;}
    break;

  case 484:
#line 4023 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry);;}
    break;

  case 485:
#line 4027 "gram1.y"
    {(yyval.hash_entry) = look_up_sym(yytext);;}
    break;

  case 486:
#line 4031 "gram1.y"
    { PTR_SYMB s;
	             s = make_local_entity( (yyvsp[(1) - (2)].hash_entry), CONSTRUCT_NAME, global_default, LOCAL);             
                    (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
                   ;}
    break;

  case 487:
#line 4052 "gram1.y"
    { (yyval.bf_node) = make_if((yyvsp[(4) - (5)].ll_node)); ;}
    break;

  case 488:
#line 4055 "gram1.y"
    { (yyval.bf_node) = make_forall((yyvsp[(4) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node)); ;}
    break;

  case 489:
#line 4059 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 490:
#line 4061 "gram1.y"
    { PTR_LLND p;	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 491:
#line 4068 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, FORALL_OP, (yyvsp[(3) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); ;}
    break;

  case 492:
#line 4072 "gram1.y"
    { (yyval.ll_node)=LLNULL;;}
    break;

  case 493:
#line 4074 "gram1.y"
    { (yyval.ll_node)=(yyvsp[(2) - (2)].ll_node);;}
    break;

  case 494:
#line 4090 "gram1.y"
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
#line 4103 "gram1.y"
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
#line 4126 "gram1.y"
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
#line 4149 "gram1.y"
    { (yyval.label) = LBNULL; ;}
    break;

  case 498:
#line 4151 "gram1.y"
    {
	       (yyval.label)  = make_label_node(fi,convci(yyleng, yytext));
	       (yyval.label)->scope = cur_scope();
	    ;}
    break;

  case 499:
#line 4158 "gram1.y"
    { make_endwhere((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 500:
#line 4160 "gram1.y"
    { make_elsewhere((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 501:
#line 4162 "gram1.y"
    { make_elsewhere_mask((yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 502:
#line 4164 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 503:
#line 4166 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), LLNULL, (yyvsp[(1) - (6)].ll_node)); ;}
    break;

  case 504:
#line 4171 "gram1.y"
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
#line 4246 "gram1.y"
    { /*PTR_SYMB s;*/
	
	      /*s = make_scalar($2, TYNULL, LOCAL);*/
  	      (yyval.bf_node) = get_bfnd(fi, POINTER_ASSIGN_STAT, SMNULL, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), LLNULL);
	    ;}
    break;

  case 506:
#line 4258 "gram1.y"
    { PTR_SYMB p;

	      p = make_scalar((yyvsp[(5) - (5)].hash_entry), TYNULL, LOCAL);
	      p->variant = LABEL_VAR;
  	      (yyval.bf_node) = get_bfnd(fi,ASSLAB_STAT, p, (yyvsp[(3) - (5)].ll_node),LLNULL,LLNULL);
            ;}
    break;

  case 507:
#line 4265 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONT_STAT,SMNULL,LLNULL,LLNULL,LLNULL); ;}
    break;

  case 509:
#line 4268 "gram1.y"
    { inioctl = NO; ;}
    break;

  case 510:
#line 4270 "gram1.y"
    { PTR_LLND	p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(10) - (10)].ll_node), LLNULL, SMNULL);
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(8) - (10)].ll_node), p, SMNULL);
	      (yyval.bf_node)= get_bfnd(fi,ARITHIF_NODE, SMNULL, (yyvsp[(4) - (10)].ll_node),
			    make_llnd(fi,EXPR_LIST, (yyvsp[(6) - (10)].ll_node), p, SMNULL), LLNULL);
	      thiswasbranch = YES;
            ;}
    break;

  case 511:
#line 4279 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (1)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT, $1, LLNULL, LLNULL, LLNULL);
*/	      endioctl(); 
            ;}
    break;

  case 512:
#line 4286 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (3)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT,$1,LLNULL,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 513:
#line 4293 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, PLAIN);
/*	      match_parameters($1, $3);
	      $$= get_bfnd(fi,PROC_STAT,$1,$3,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 514:
#line 4301 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,RETURN_STAT,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = YES;
	    ;}
    break;

  case 515:
#line 4306 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,(yyvsp[(1) - (3)].token),SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = ((yyvsp[(1) - (3)].token) == STOP_STAT);
	    ;}
    break;

  case 516:
#line 4311 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CYCLE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 517:
#line 4314 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, EXIT_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 518:
#line 4317 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, ALLOCATE_STMT,  SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc, LLNULL); ;}
    break;

  case 519:
#line 4320 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, DEALLOCATE_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc , LLNULL); ;}
    break;

  case 520:
#line 4323 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, NULLIFY_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 521:
#line 4326 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_NODE, SMNULL, (yyvsp[(4) - (8)].ll_node), (yyvsp[(6) - (8)].ll_node), (yyvsp[(8) - (8)].ll_node)); ;}
    break;

  case 522:
#line 4344 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 523:
#line 4348 "gram1.y"
    {
	      (yyval.bf_node)=get_bfnd(fi,GOTO_NODE,SMNULL,LLNULL,LLNULL,(PTR_LLND)(yyvsp[(3) - (3)].ll_node));
	      thiswasbranch = YES;
	    ;}
    break;

  case 524:
#line 4353 "gram1.y"
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
#line 4372 "gram1.y"
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
#line 4391 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,COMGOTO_NODE, SMNULL, (yyvsp[(4) - (7)].ll_node), (yyvsp[(7) - (7)].ll_node), LLNULL); ;}
    break;

  case 529:
#line 4399 "gram1.y"
    { (yyval.symbol) = make_procedure((yyvsp[(3) - (4)].hash_entry), YES); ;}
    break;

  case 530:
#line 4403 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 531:
#line 4408 "gram1.y"
    { 
               (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
               endioctl();
            ;}
    break;

  case 532:
#line 4415 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 533:
#line 4417 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 534:
#line 4419 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,LABEL_ARG,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 535:
#line 4422 "gram1.y"
    { (yyval.token) = PAUSE_NODE; ;}
    break;

  case 536:
#line 4423 "gram1.y"
    { (yyval.token) = STOP_STAT; ;}
    break;

  case 537:
#line 4434 "gram1.y"
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
#line 4449 "gram1.y"
    { intonly = YES; ;}
    break;

  case 539:
#line 4453 "gram1.y"
    { intonly = NO; ;}
    break;

  case 540:
#line 4461 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 541:
#line 4464 "gram1.y"
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
#line 4474 "gram1.y"
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
#line 4487 "gram1.y"
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
#line 4500 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 545:
#line 4504 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 546:
#line 4507 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 547:
#line 4510 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 548:
#line 4514 "gram1.y"
    { (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (4)].ll_node);
		  (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (4)].bf_node); ;}
    break;

  case 549:
#line 4523 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 550:
#line 4526 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 551:
#line 4530 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 552:
#line 4532 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 553:
#line 4538 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 554:
#line 4542 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, BACKSPACE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 555:
#line 4544 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, REWIND_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 556:
#line 4546 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, ENDFILE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 557:
#line 4553 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 558:
#line 4557 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 559:
#line 4559 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, OPEN_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 560:
#line 4561 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, CLOSE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 561:
#line 4565 "gram1.y"
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
#line 4584 "gram1.y"
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
#line 4600 "gram1.y"
    { PTR_LLND p;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"unit";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, p, (yyvsp[(2) - (3)].ll_node), SMNULL);
		  endioctl();
		;}
    break;

  case 564:
#line 4611 "gram1.y"
    { 
		  (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);
		  endioctl();
		 ;}
    break;

  case 565:
#line 4618 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); endioctl();;}
    break;

  case 566:
#line 4620 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl();;}
    break;

  case 567:
#line 4624 "gram1.y"
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
#line 4650 "gram1.y"
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
#line 4665 "gram1.y"
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
#line 4680 "gram1.y"
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
#line 4697 "gram1.y"
    { PTR_LLND p;
                  
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 572:
#line 4705 "gram1.y"
    { PTR_LLND p;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 573:
#line 4714 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  (yyval.ll_node)->entry.string_val = copys(yytext);
		  (yyval.ll_node)->type = global_string;
	        ;}
    break;

  case 574:
#line 4722 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, READ_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 575:
#line 4727 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, WRITE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 576:
#line 4732 "gram1.y"
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
#line 4754 "gram1.y"
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
#line 4770 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);;}
    break;

  case 579:
#line 4772 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST);;}
    break;

  case 580:
#line 4776 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 581:
#line 4778 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
		;}
    break;

  case 582:
#line 4785 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);  (yyval.ll_node)->type = (yyvsp[(1) - (1)].ll_node)->type;;}
    break;

  case 583:
#line 4787 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 584:
#line 4789 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 585:
#line 4793 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 586:
#line 4795 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 587:
#line 4797 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 588:
#line 4799 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 589:
#line 4801 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 590:
#line 4803 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 591:
#line 4807 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);
	          (yyval.ll_node)->type = global_complex; ;}
    break;

  case 592:
#line 4810 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (3)].ll_node)->type; ;}
    break;

  case 593:
#line 4813 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 594:
#line 4819 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 595:
#line 4825 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 596:
#line 4833 "gram1.y"
    { inioctl = YES; ;}
    break;

  case 597:
#line 4837 "gram1.y"
    { startioctl();;}
    break;

  case 598:
#line 4845 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 599:
#line 4847 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 600:
#line 4851 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 601:
#line 4853 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 602:
#line 4855 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,(yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 603:
#line 4860 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 604:
#line 4865 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 605:
#line 4870 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 606:
#line 4875 "gram1.y"
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
#line 4884 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 608:
#line 4889 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 609:
#line 4894 "gram1.y"
    { comments = cur_comment = CMNULL; ;}
    break;

  case 610:
#line 4896 "gram1.y"
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

  case 667:
#line 4972 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 668:
#line 4975 "gram1.y"
    {  
                PTR_SYMB s;
                PTR_LLND q;
                s = (yyvsp[(8) - (8)].ll_node)->entry.Template.ll_ptr1->entry.Template.symbol;
                s->attr = s->attr | COMMON_BIT;
                q = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(8) - (8)].ll_node), q, LLNULL); 
              ;}
    break;

  case 669:
#line 4984 "gram1.y"
    { PTR_SYMB s;
                if((yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2)
                {
                  s = (yyvsp[(3) - (3)].ll_node)->entry.Template.ll_ptr1->entry.Template.symbol;
                  s->attr = s->attr | COMMON_BIT;
                }
	        add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	      ;}
    break;

  case 670:
#line 4995 "gram1.y"
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

  case 671:
#line 5015 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DYNAMIC_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 672:
#line 5019 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 673:
#line 5021 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 674:
#line 5025 "gram1.y"
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

  case 675:
#line 5038 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INHERIT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 676:
#line 5042 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 677:
#line 5044 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 678:
#line 5048 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
              else
                s->attr = s->attr | INHERIT_BIT;        
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 679:
#line 5059 "gram1.y"
    { PTR_LLND q;
             q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              /* (void)fprintf(stderr,"hpf.gram: shadow\n");*/ 
	     (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_DIR,SMNULL,q,(yyvsp[(4) - (4)].ll_node),LLNULL);
            ;}
    break;

  case 680:
#line 5070 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 681:
#line 5074 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 682:
#line 5076 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 683:
#line 5080 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 684:
#line 5082 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 685:
#line 5092 "gram1.y"
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

  case 686:
#line 5104 "gram1.y"
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

  case 687:
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

  case 688:
#line 5144 "gram1.y"
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

  case 689:
#line 5166 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 690:
#line 5172 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 691:
#line 5181 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 692:
#line 5189 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 693:
#line 5195 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 694:
#line 5203 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 695:
#line 5210 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 696:
#line 5216 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 697:
#line 5225 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 698:
#line 5229 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 699:
#line 5235 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 700:
#line 5243 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 701:
#line 5257 "gram1.y"
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

  case 702:
#line 5270 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 703:
#line 5276 "gram1.y"
    { PTR_LLND q;
             if(!(yyvsp[(4) - (5)].ll_node))
               err("Distribution format list is omitted", 51);
            /* if($6)
               err("NEW_VALUE specification in DISTRIBUTE directive");*/
             q = set_ll_list((yyvsp[(3) - (5)].ll_node),LLNULL,EXPR_LIST);
	     (yyval.bf_node) = get_bfnd(fi,DVM_DISTRIBUTE_DIR,SMNULL,q,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node));
            ;}
    break;

  case 704:
#line 5292 "gram1.y"
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

  case 705:
#line 5307 "gram1.y"
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

  case 706:
#line 5335 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 707:
#line 5337 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 708:
#line 5341 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 709:
#line 5343 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 710:
#line 5347 "gram1.y"
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

  case 711:
#line 5376 "gram1.y"
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

  case 712:
#line 5399 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 713:
#line 5419 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 714:
#line 5421 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 715:
#line 5425 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 716:
#line 5446 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 717:
#line 5448 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 718:
#line 5451 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 719:
#line 5460 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 720:
#line 5464 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 721:
#line 5469 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 722:
#line 5471 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 723:
#line 5473 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 724:
#line 5475 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 725:
#line 5481 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 726:
#line 5483 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 727:
#line 5487 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 728:
#line 5497 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
    break;

  case 729:
#line 5501 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 730:
#line 5503 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 731:
#line 5508 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 732:
#line 5512 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 733:
#line 5516 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 734:
#line 5522 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 735:
#line 5532 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 736:
#line 5534 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 737:
#line 5538 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 738:
#line 5540 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 739:
#line 5542 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 740:
#line 5549 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 741:
#line 5566 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 742:
#line 5568 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 743:
#line 5572 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 744:
#line 5574 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 745:
#line 5578 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 746:
#line 5585 "gram1.y"
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

  case 747:
#line 5595 "gram1.y"
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

  case 748:
#line 5624 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 749:
#line 5639 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 750:
#line 5646 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 751:
#line 5664 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 752:
#line 5666 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 753:
#line 5670 "gram1.y"
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

  case 754:
#line 5684 "gram1.y"
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

  case 755:
#line 5710 "gram1.y"
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

  case 756:
#line 5723 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 757:
#line 5739 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 758:
#line 5741 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 759:
#line 5744 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 760:
#line 5746 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 761:
#line 5752 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 762:
#line 5756 "gram1.y"
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

  case 763:
#line 5784 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 764:
#line 5786 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 765:
#line 5790 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 766:
#line 5798 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 767:
#line 5804 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 768:
#line 5807 "gram1.y"
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

  case 769:
#line 5858 "gram1.y"
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

  case 770:
#line 5917 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 771:
#line 5919 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 772:
#line 5922 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 773:
#line 5926 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 774:
#line 5930 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 775:
#line 5934 "gram1.y"
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 776:
#line 5951 "gram1.y"
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

  case 777:
#line 5963 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 778:
#line 5967 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 779:
#line 5971 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 780:
#line 5981 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 781:
#line 5986 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 782:
#line 5993 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 783:
#line 6001 "gram1.y"
    {ndim = 0;;}
    break;

  case 784:
#line 6002 "gram1.y"
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

  case 785:
#line 6013 "gram1.y"
    { PTR_LLND  q;
             if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		q = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL);
	      ++ndim;
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), q, EXPR_LIST);
            ;}
    break;

  case 786:
#line 6024 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 787:
#line 6026 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 788:
#line 6030 "gram1.y"
    {PTR_SYMB s;
           /* s = make_scalar($1,TYNULL,LOCAL);*/
            s = make_array((yyvsp[(1) - (1)].hash_entry),TYNULL,LLNULL,0,LOCAL);
            s->attr = s->attr | DVM_POINTER_BIT;
            if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT))
               errstr( "Inconsistent declaration of identifier %s", s->ident, 16);     
            (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL,s);
            ;}
    break;

  case 789:
#line 6041 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 790:
#line 6045 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 791:
#line 6047 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 792:
#line 6051 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 793:
#line 6062 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 794:
#line 6066 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 795:
#line 6068 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 796:
#line 6072 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 797:
#line 6084 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 798:
#line 6086 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 799:
#line 6093 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 800:
#line 6095 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 801:
#line 6099 "gram1.y"
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

  case 802:
#line 6115 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 803:
#line 6125 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                 ;}
    break;

  case 804:
#line 6134 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 805:
#line 6136 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 807:
#line 6143 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 808:
#line 6146 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 809:
#line 6151 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
           errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
         ;}
    break;

  case 810:
#line 6161 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 811:
#line 6163 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 812:
#line 6167 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 813:
#line 6169 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 814:
#line 6177 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 815:
#line 6179 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 816:
#line 6183 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 817:
#line 6185 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 828:
#line 6202 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 829:
#line 6207 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 830:
#line 6211 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 831:
#line 6215 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 832:
#line 6219 "gram1.y"
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

  case 833:
#line 6232 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 834:
#line 6236 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 835:
#line 6240 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 836:
#line 6244 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 837:
#line 6247 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 838:
#line 6249 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 839:
#line 6251 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 840:
#line 6255 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 841:
#line 6257 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 842:
#line 6261 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 843:
#line 6266 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 844:
#line 6270 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 845:
#line 6274 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 846:
#line 6276 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 847:
#line 6280 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 848:
#line 6288 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 849:
#line 6294 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 850:
#line 6300 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 851:
#line 6304 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 852:
#line 6306 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 853:
#line 6310 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 854:
#line 6312 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 855:
#line 6316 "gram1.y"
    { /*  PTR_LLND p;
                       p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
                       p->entry.string_val = (char *) "corner";
                       p->type = global_string;
                   */
                   (yyvsp[(1) - (7)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (7)].ll_node);  
                   (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 856:
#line 6328 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 857:
#line 6330 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 858:
#line 6334 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 859:
#line 6338 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 860:
#line 6340 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 861:
#line 6344 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 862:
#line 6346 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 863:
#line 6348 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 864:
#line 6350 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 865:
#line 6352 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 866:
#line 6354 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 867:
#line 6356 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 868:
#line 6360 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 869:
#line 6364 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 870:
#line 6368 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 871:
#line 6372 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 872:
#line 6376 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 873:
#line 6383 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 874:
#line 6389 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 875:
#line 6393 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 876:
#line 6396 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 877:
#line 6400 "gram1.y"
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

  case 878:
#line 6413 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 879:
#line 6415 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 880:
#line 6419 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 881:
#line 6421 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 882:
#line 6426 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 883:
#line 6432 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 884:
#line 6438 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 885:
#line 6444 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 886:
#line 6450 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 887:
#line 6456 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 888:
#line 6462 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 889:
#line 6468 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 890:
#line 6474 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 891:
#line 6483 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 892:
#line 6489 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 893:
#line 6506 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 894:
#line 6514 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 895:
#line 6522 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 896:
#line 6524 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 897:
#line 6526 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 898:
#line 6530 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 899:
#line 6534 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 900:
#line 6536 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 901:
#line 6540 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 902:
#line 6542 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 903:
#line 6550 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 904:
#line 6554 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 905:
#line 6565 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 906:
#line 6569 "gram1.y"
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

  case 907:
#line 6587 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 908:
#line 6589 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 909:
#line 6593 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 910:
#line 6595 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 911:
#line 6599 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 912:
#line 6601 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 913:
#line 6605 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 914:
#line 6609 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 915:
#line 6613 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 916:
#line 6622 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 917:
#line 6626 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 918:
#line 6630 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 919:
#line 6635 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 920:
#line 6639 "gram1.y"
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

  case 921:
#line 6651 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 922:
#line 6653 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 923:
#line 6657 "gram1.y"
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 924:
#line 6662 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 925:
#line 6666 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 926:
#line 6668 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 927:
#line 6672 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 928:
#line 6674 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 929:
#line 6678 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 930:
#line 6683 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 931:
#line 6690 "gram1.y"
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

  case 932:
#line 6713 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 933:
#line 6715 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 934:
#line 6717 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 935:
#line 6719 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 936:
#line 6721 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 937:
#line 6725 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 938:
#line 6736 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 939:
#line 6740 "gram1.y"
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

  case 940:
#line 6755 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 941:
#line 6762 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 942:
#line 6768 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 943:
#line 6770 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 944:
#line 6774 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 945:
#line 6778 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 946:
#line 6786 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 947:
#line 6790 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 948:
#line 6794 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 949:
#line 6802 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 950:
#line 6807 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 951:
#line 6821 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 952:
#line 6823 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 953:
#line 6827 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 954:
#line 6829 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 955:
#line 6838 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 956:
#line 6840 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 957:
#line 6842 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 958:
#line 6844 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 959:
#line 6880 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 960:
#line 6884 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 961:
#line 6888 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 962:
#line 6892 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 963:
#line 6896 "gram1.y"
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

  case 964:
#line 6908 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 965:
#line 6910 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 966:
#line 6914 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 967:
#line 6917 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 968:
#line 6919 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 969:
#line 6923 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 970:
#line 6928 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 971:
#line 6935 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 972:
#line 6938 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 973:
#line 6946 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 974:
#line 6950 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 975:
#line 6954 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 976:
#line 6957 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 977:
#line 6964 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 978:
#line 6968 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 979:
#line 6972 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 980:
#line 6976 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 981:
#line 6980 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 982:
#line 6984 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 983:
#line 6987 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 984:
#line 6989 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 985:
#line 6993 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 986:
#line 6995 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 987:
#line 6997 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 988:
#line 7001 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 989:
#line 7005 "gram1.y"
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

  case 990:
#line 7017 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 991:
#line 7019 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 992:
#line 7023 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 993:
#line 7025 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 994:
#line 7029 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 995:
#line 7031 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 996:
#line 7035 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 997:
#line 7039 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 998:
#line 7045 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 999:
#line 7057 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1000:
#line 7059 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1001:
#line 7063 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1002:
#line 7065 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1003:
#line 7069 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1031:
#line 7107 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1032:
#line 7113 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1033:
#line 7119 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1034:
#line 7125 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1035:
#line 7131 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1036:
#line 7135 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1046:
#line 7152 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1047:
#line 7157 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1048:
#line 7162 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1049:
#line 7168 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1050:
#line 7174 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1051:
#line 7180 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1052:
#line 7185 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1053:
#line 7191 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1054:
#line 7197 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1055:
#line 7203 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1056:
#line 7210 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1057:
#line 7216 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1058:
#line 7222 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1059:
#line 7229 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1061:
#line 7235 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1062:
#line 7241 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1063:
#line 7248 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1064:
#line 7254 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1065:
#line 7260 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1066:
#line 7266 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1067:
#line 7272 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1068:
#line 7278 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1069:
#line 7284 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1070:
#line 7290 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1071:
#line 7296 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1072:
#line 7302 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1073:
#line 7308 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1074:
#line 7314 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1075:
#line 7324 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1076:
#line 7329 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1077:
#line 7335 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1078:
#line 7339 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1083:
#line 7351 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1084:
#line 7359 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1085:
#line 7365 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1086:
#line 7371 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1087:
#line 7376 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1088:
#line 7382 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1089:
#line 7389 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1090:
#line 7395 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1091:
#line 7399 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1098:
#line 7413 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1099:
#line 7422 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1100:
#line 7426 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1101:
#line 7432 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1102:
#line 7439 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1103:
#line 7446 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1104:
#line 7453 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1105:
#line 7462 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1106:
#line 7468 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1107:
#line 7474 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1108:
#line 7478 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1111:
#line 7488 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1112:
#line 7494 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1113:
#line 7500 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1114:
#line 7504 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1117:
#line 7515 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1118:
#line 7521 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1119:
#line 7527 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1120:
#line 7532 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1121:
#line 7540 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1122:
#line 7546 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1123:
#line 7551 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1124:
#line 7558 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1125:
#line 7562 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1137:
#line 7582 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1138:
#line 7587 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1139:
#line 7592 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1140:
#line 7599 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1141:
#line 7604 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1142:
#line 7610 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1143:
#line 7616 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1144:
#line 7621 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1145:
#line 7626 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1146:
#line 7631 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1147:
#line 7635 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1148:
#line 7640 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1149:
#line 7645 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1150:
#line 7649 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1151:
#line 7654 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1152:
#line 7658 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1153:
#line 7664 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1154:
#line 7669 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1155:
#line 7675 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1156:
#line 7680 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1157:
#line 7686 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1158:
#line 7696 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1159:
#line 7700 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1160:
#line 7704 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1161:
#line 7708 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1162:
#line 7713 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1163:
#line 7716 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1170:
#line 7729 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1171:
#line 7733 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1172:
#line 7737 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1173:
#line 7739 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1174:
#line 7741 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1175:
#line 7745 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1176:
#line 7747 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1177:
#line 7749 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1178:
#line 7753 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1179:
#line 7755 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1180:
#line 7759 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1181:
#line 7761 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1182:
#line 7765 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1183:
#line 7768 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1184:
#line 7771 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1185:
#line 7776 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1186:
#line 7778 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1187:
#line 7780 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1188:
#line 7782 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1189:
#line 7784 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1190:
#line 7788 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1191:
#line 7792 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1192:
#line 7797 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1193:
#line 7801 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1194:
#line 7803 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1195:
#line 7807 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1196:
#line 7809 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1197:
#line 7813 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1198:
#line 7817 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1204:
#line 7828 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1205:
#line 7832 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1206:
#line 7836 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1207:
#line 7840 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1208:
#line 7844 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1209:
#line 7848 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1210:
#line 7850 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1213:
#line 7858 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1214:
#line 7862 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1215:
#line 7866 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1216:
#line 7868 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1220:
#line 7878 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1221:
#line 7882 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1222:
#line 7886 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1223:
#line 7890 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1224:
#line 7892 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1225:
#line 7896 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1226:
#line 7900 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;


/* Line 1267 of yacc.c.  */
#line 13499 "gram1.tab.c"
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



