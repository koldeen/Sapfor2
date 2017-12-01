#include "../include/SageUtils.hpp"

const char * SageTransform::SageUtils::decodeStmtVariant(int variant) {
	switch (variant) {
		case 100 : return "GLOBAL";
		case 101 : return "PROG_HEDR";
		case 102 : return "PROC_HEDR";
		case 103 : return "BASIC_BLOCK";
		case 104 : return "CONTROL_END";
		case 105 : return "IF_NODE";
		case 106 : return "LOOP_NODE";
		case 107 : return "FOR_NODE";
		case 108 : return "FORALL_NODE";
		case 109 : return "WHILE_NODE";
		case 110 : return "EXIT_NODE";
		case 111 : return "ASSIGN_STAT";
		case 112 : return "M_ASSIGN_STAT";
		case 113 : return "PROC_STAT";
		case 114	/* accumulation statements */ : return "SUM_ACC";
		case 115 : return "MULT_ACC";
		case 116 : return "MAX_ACC";
		case 117 : return "MIN_ACC";
		case 118 : return "CAT_ACC";
		case 119 : return "OR_ACC";
		case 120 : return "AND_ACC";
		case 121 : return "READ_STAT";
		case 122 : return "WRITE_STAT";
		case 123 : return "OTHERIO_STAT";
		case 124 : return "CDOALL_NODE";
		case 125 : return "SDOALL_NODE";
		case 126 : return "DOACROSS_NODE";
		case 127 : return "CDOACROSS_NODE";
		case 128  /* DVM-F */ : return "DVM_INTERVAL_DIR";
		case 129  /* DVM-F */ : return "DVM_ENDINTERVAL_DIR";
		case 130 : return "FUNC_HEDR";
		case 131 : return "WHERE_NODE";
		case 132 : return "ALLDO_NODE";
		case 133 : return "IDENTIFY";
		case 134 : return "FORMAT_STAT";
		case 135 : return "STOP_STAT";
		case 136 : return "RETURN_STAT";
		case 137 : return "ELSEIF_NODE";
		case 138 : return "ARITHIF_NODE";
		case 139 : return "GOTO_NODE";
		case 140 : return "ASSGOTO_NODE";
		case 141 : return "COMGOTO_NODE";
		case 142 : return "PAUSE_NODE";
		case 143 : return "STOP_NODE";
		case 144 : return "ASSLAB_STAT";
		case 145 : return "LOGIF_NODE";
		case 146  /* DVM-F */ : return "DVM_DEBUG_DIR";
		case 147  /* DVM-F */ : return "DVM_ENDDEBUG_DIR";
		case 148  /* DVM-F */ : return "DVM_TRACEON_DIR";
		case 149  /* DVM-F */ : return "DVM_TRACEOFF_DIR";
		case 150 : return "BLOB";
		case 151 : return "SIZES";
		case 152 : return "COMMENT_STAT";
		case 153 : return "CONT_STAT";
		case 154 : return "VAR_DECL";
		case 155 : return "PARAM_DECL";
		case 156 : return "COMM_STAT";
		case 157 : return "EQUI_STAT";
		case 158 : return "IMPL_DECL";
		case 159 : return "DATA_DECL";
		case 160 : return "SAVE_DECL";
		case 162 : return "ENTRY_STAT";
		case 163 : return "STMTFN_STAT";
		case 164 : return "DIM_STAT";
		case 165 : return "BLOCK_DATA";
		case 166 : return "EXTERN_STAT";
		case 167 : return "INTRIN_STAT";
		case 168	/* New added for VPC */ : return "ENUM_DECL";
		case 169	/* New added for VPC */ : return "CLASS_DECL";
		case 170	/* New added for VPC */ : return "UNION_DECL";
		case 171	/* New added for VPC */ : return "STRUCT_DECL";
		case 172	/* New added for VPC */ : return "DERIVED_CLASS_DECL";
		case 173	/* New added for VPC */ : return "EXPR_STMT_NODE";
		case 174	/* New added for VPC */ : return "DO_WHILE_NODE";
		case 175	/* New added for VPC */ : return "SWITCH_NODE";
		case 176	/* New added for VPC */ : return "CASE_NODE";
		case 177	/* New added for VPC */ : return "DEFAULT_NODE";
		case 178	/* New added for VPC */ : return "BREAK_NODE";
		case 179	/* New added for VPC */ : return "CONTINUE_NODE";
		case 180	/* New added for VPC */ : return "RETURN_NODE";
		case 181	/* New added for VPC */ : return "ASM_NODE";
		case 182	/* New added for CC++ */ : return "SPAWN_NODE";
		case 183	/* New added for CC++ */ : return "PARFOR_NODE";
		case 184	/* New added for CC++ */ : return "PAR_NODE";
		case 185	/* New added for VPC */ : return "LABEL_STAT";
		case 186	/* Fortran M */ : return "PROS_COMM";
		case 187	/* attribute declaration */ : return "ATTR_DECL";
		case 188 : return "NAMELIST_STAT";
		case 189	/* NEW added for VPC */ : return "FUTURE_STMT";
		case 190	/* NEW added for PC++ */ : return "COLLECTION_DECL";
		case 191     /* added by dbg for templates */ : return "TEMPLATE_DECL";
		case 192     /* added by dbg for template function*/ : return "TEMPLATE_FUNDECL";
		case 193     /* added for pC++ */ : return "TECLASS_DECL";
		case 194     /*F95*/ : return "ELSEWH_NODE";
		case 195     /*F95*/ : return "STATIC_STMT";
		case 196     /*F95*/ : return "INCLUDE_LINE";
		case 197     /*C,C++*/ : return "PREPROCESSOR_DIR";
		case 200 : return "PRINT_STAT";
		case 201 : return "BACKSPACE_STAT";
		case 202 : return "REWIND_STAT";
		case 203 : return "ENDFILE_STAT";
		case 204 : return "INQUIRE_STAT";
		case 205 : return "OPEN_STAT";
		case 206 : return "CLOSE_STAT";
		case 207	/* Added by PHB for 'extern "C" {}' */ : return "EXTERN_C_STAT";
		case 208 : return "INCLUDE_STAT";
		case 209     /* added by dbg for C++ exceptions  */ : return "TRY_STAT";
		case 210     /* moreexcpt handling (part of try) */ : return "CATCH_STAT";
		case 211  /* DVM-F */ : return "DVM_PARALLEL_ON_DIR";
		case 212  /* DVM-F */ : return "DVM_SHADOW_START_DIR";
		case 213  /* DVM-F */ : return "DVM_SHADOW_GROUP_DIR";
		case 214  /* DVM-F */ : return "DVM_SHADOW_WAIT_DIR";
		case 215  /* DVM-F */ : return "DVM_REDUCTION_START_DIR";
		case 216  /* DVM-F */ : return "DVM_REDUCTION_GROUP_DIR";
		case 217  /* DVM-F */ : return "DVM_REDUCTION_WAIT_DIR";
		case 218  /* DVM-F */ : return "DVM_DYNAMIC_DIR";
		case 219  /* DVM-F */ : return "DVM_ALIGN_DIR";
		case 220  /* DVM-F */ : return "DVM_REALIGN_DIR";
		case 221  /* DVM-F */ : return "DVM_REALIGN_NEW_DIR";
		case 222  /* DVM-F */ : return "DVM_REMOTE_ACCESS_DIR";
		case 223  /* HPF */ : return "HPF_INDEPENDENT_DIR";
		case 224  /* DVM-F */ : return "DVM_SHADOW_DIR";
		case 225     /* Following added for PCF Fortran */ : return "PARDO_NODE";
		case 226 : return "PARSECTIONS_NODE";
		case 227 : return "SECTION_NODE";
		case 228 : return "GUARDS_NODE";
		case 229 : return "LOCK_NODE";
		case 230 : return "UNLOCK_NODE";
		case 231 : return "CRITSECTION_NODE";
		case 232 : return "POST_NODE";
		case 233 : return "WAIT_NODE";
		case 234 : return "CLEAR_NODE";
		case 235 : return "POSTSEQ_NODE";
		case 236 : return "WAITSEQ_NODE";
		case 237 : return "SETSEQ_NODE";
		case 238 : return "ASSIGN_NODE";
		case 239 : return "RELEASE_NODE";
		case 240 : return "PRIVATE_NODE";
		case 241 : return "SCOMMON_NODE";
		case 242 : return "PARREGION_NODE";
		case 243 : return "PDO_NODE";
		case 244 : return "PSECTIONS_NODE";
		case 245 : return "SINGLEPROCESS_NODE";
		case 246 : return "SKIPPASTEOF_NODE";
		case 247 /* DVM-F */ : return "DVM_NEW_VALUE_DIR";
		case 248 /* DVM-F */ : return "DVM_VAR_DECL";
		case 249 /* DVM-F */ : return "DVM_POINTER_DIR";
		case 250        /* Added for Fortran 90 */ : return "INTENT_STMT";
		case 251 : return "OPTIONAL_STMT";
		case 252 : return "PUBLIC_STMT";
		case 253 : return "PRIVATE_STMT";
		case 254 : return "ALLOCATABLE_STMT";
		case 255 : return "POINTER_STMT";
		case 256 : return "TARGET_STMT";
		case 257 : return "ALLOCATE_STMT";
		case 258 : return "NULLIFY_STMT";
		case 259 : return "DEALLOCATE_STMT";
		case 260 : return "SEQUENCE_STMT";
		case 261 : return "CYCLE_STMT";
		case 262 : return "EXIT_STMT";
		case 263 : return "CONTAINS_STMT";
		case 264 : return "WHERE_BLOCK_STMT";
		case 265 : return "MODULE_STMT";
		case 266 : return "USE_STMT";
		case 267 : return "INTERFACE_STMT";
		case 268 : return "MODULE_PROC_STMT";
		case 269 : return "OVERLOADED_ASSIGN_STAT";
		case 270 : return "POINTER_ASSIGN_STAT";
		case 271 : return "OVERLOADED_PROC_STAT";
		case 275 : return "DECOMPOSITION_STMT";
		case 276 : return "ALIGN_STMT";
		case 277  /* DVM-F */  : return "DVM_DISTRIBUTE_DIR";
		case 278 : return "REDUCE_STMT";
		case 279  /* Fortran M */ : return "PROS_HEDR";
		case 280  /* Fortran M */ : return "PROS_STAT";
		case 281  /* Fortran M */ : return "PROS_STAT_LCTN";
		case 282  /* Fortran M */ : return "PROS_STAT_SUBM";
		case 283  /* Fortran M */ : return "PROCESSES_STAT";
		case 284  /* Fortran M */ : return "PROCESSES_END";
		case 285  /* Fortran M */ : return "PROCESS_DO_STAT";
		case 286  /* Fortran M */ : return "PROCESSORS_STAT";
		case 287  /* Fortran M */ : return "CHANNEL_STAT";
		case 288  /* Fortran M */ : return "MERGER_STAT";
		case 289  /* Fortran M */ : return "MOVE_PORT";
		case 290  /* Fortran M */ : return "SEND_STAT";
		case 291  /* Fortran M */ : return "RECEIVE_STAT";
		case 292  /* Fortran M */ : return "ENDCHANNEL_STAT";
		case 293  /* Fortran M */ : return "PROBE_STAT";
		case 294  /* Fortran M */ : return "INPORT_DECL";
		case 295  /* Fortran M */ : return "OUTPORT_DECL";
		case 296  /* HPF */ : return "HPF_TEMPLATE_STAT";
		case 297  /* HPF */     : return "HPF_ALIGN_STAT";
		case 298  /* HPF */ : return "HPF_PROCESSORS_STAT";
		case 299  /* DVM-F */ : return "DVM_REDISTRIBUTE_DIR";
					case 300: return "INT_VAL";
		case 301: return "FLOAT_VAL";
		case 302: return "DOUBLE_VAL";
		case 303: return "BOOL_VAL";
		case 304: return "CHAR_VAL";
		case 305: return "STRING_VAL";
		case 306: return "CONST_REF";
		case 307: return "VAR_REF";
		case 308: return "ARRAY_REF";
		case 309: return "RECORD_REF";   /* diff struct between Blaze and VPC++ */
		case 310: return "ENUM_REF";
		case 311: return "VAR_LIST";
		case 312: return "EXPR_LIST";
		case 313: return "RANGE_LIST";
		case 314: return "CASE_CHOICE";
		case 315: return "DEF_CHOICE";
		case 316: return "VARIANT_CHOICE";
		case 317: return "COMPLEX_VAL";
		case 318: return "LABEL_REF";
		case 319: return "KEYWORD_VAL";   /* Strings to be printed with quotes */
		case 324: return "DDOT";
		case 325: return "RANGE_OP";
		case 326: return "UPPER_OP";
		case 327: return "LOWER_OP";
		case 328: return "EQ_OP";
		case 329: return "LT_OP";
		case 330: return "GT_OP";
		case 331: return "NOTEQL_OP";
		case 332: return "LTEQL_OP";
		case 333: return "GTEQL_OP";
		case 334: return "ADD_OP";
		case 335: return "SUBT_OP";
		case 336: return "OR_OP";
		case 337: return "MULT_OP";
		case 338: return "DIV_OP";
		case 339: return "MOD_OP";
		case 340: return "AND_OP";
		case 341: return "EXP_OP";
		case 342: return "ARRAY_MULT";
		case 343: return "CONCAT_OP";	/* cancatenation of strings */
		case 344: return "XOR_OP";	/* .XOR. in fortran */
		case 345: return "EQV_OP";	/* .EQV. in fortran */
		case 346: return "NEQV_OP";	/* .NEQV. in fortran */
		case 350: return "MINUS_OP";	/* unary operations */
		case 351: return "NOT_OP";
		case 352: return "ASSGN_OP";	/* New ADDED For VPC */
		case 353: return "DEREF_OP";	/* New ADDED For VPC */
		case 354: return "POINTST_OP";	/* New ADDED For VPC */	/* ptr->x  */
		case 355: return "FUNCTION_OP";	/* New ADDED For VPC */	/* (*DD)() */
		case 356: return "MINUSMINUS_OP";	/* New ADDED For VPC */
		case 357: return "PLUSPLUS_OP";	/* New ADDED For VPC */
		case 358: return "BITAND_OP";	/* New ADDED For VPC */
		case 359: return "BITOR_OP";	/* New ADDED For VPC */
		case 360: return "STAR_RANGE";	/* operations with no operands 360.. */
		case 370: return "PROC_CALL";
		case 371: return "FUNC_CALL";
		case 380: return "CONSTRUCTOR_REF";
		case 381: return "ACCESS_REF";
		case 382: return "CONS";
		case 383: return "ACCESS";
		case 384: return "IOACCESS";
		case 385: return "CONTROL_LIST";
		case 386: return "SEQ";
		case 387: return "SPEC_PAIR";
		case 388: return "COMM_LIST";
		case 389: return "STMT_STR";
		case 390: return "EQUI_LIST";
		case 391: return "IMPL_TYPE";
		case 392: return "STMTFN_DECL";
		case 393: return "BIT_COMPLEMENT_OP";
		case 394: return "EXPR_IF";
		case 395: return "EXPR_IF_BODY";
		case 396: return "FUNCTION_REF";
		case 397: return "LSHIFT_OP";
		case 398: return "RSHIFT_OP";
		case 399: return "UNARY_ADD_OP";
		case 400: return "SIZE_OP";
		case 401: return "INTEGER_DIV_OP";
		case 402: return "SUB_OP";
		case 403: return "LE_OP";	/* New added for VPC */
		case 404: return "GE_OP";	/* New added for VPC */
		case 405: return "NE_OP";	/* New added for VPC */
		case 406: return "CLASSINIT_OP";	/* New added for VPC */
		case 407: return "CAST_OP";	/* New added for VPC */
		case 408: return "ADDRESS_OP";	/* New added for VPC */
		case 409: return "POINSTAT_OP";	/* New added for VPC */    
		case 410: return "COPY_NODE";	/* New added for VPC */    
		case 411: return "INIT_LIST";	/* New added for VPC */    
		case 412: return "VECTOR_CONST";	/* New added for VPC */    
		case 413: return "BIT_NUMBER";	/* New added for VPC */    
		case 414: return "ARITH_ASSGN_OP";	/* New added for VPC */    
		case 415: return "ARRAY_OP";	/* New added for VPC */   
		case 416: return "NEW_OP";	/* New added for VPC */    
		case 417: return "DELETE_OP";	/* New added for VPC */
		case 418: return "NAMELIST_LIST";
		case 419: return "THIS_NODE";	/* New added for VPC */    
		case 420: return "SCOPE_OP";	/* New added for VPC */    
		case 421: return "PLUS_ASSGN_OP";	/* New added for VPC */    
		case 422: return "MINUS_ASSGN_OP";	/* New added for VPC */    
		case 423: return "AND_ASSGN_OP";	/* New added for VPC */    
		case 424: return "IOR_ASSGN_OP";	/* New added for VPC */    
		case 425: return "MULT_ASSGN_OP";	/* New added for VPC */    
		case 426: return "DIV_ASSGN_OP";	/* New added for VPC */    
		case 427: return "MOD_ASSGN_OP";	/* New added for VPC */    
		case 428: return "XOR_ASSGN_OP";	/* New added for VPC */    
		case 429: return "LSHIFT_ASSGN_OP";	/* New added for VPC */    
		case 430: return "RSHIFT_ASSGN_OP";	/* New added for VPC */    
		case 431: return "ORDERED_OP";     /* Following added for PCF FORTRAN */
		case 432: return "EXTEND_OP";
		case 433: return "MAXPARALLEL_OP";
		case 434: return "SAMETYPE_OP";
		case 450: return "TYPE_REF";     /* Added for FORTRAN 90 */
		case 451: return "STRUCTURE_CONSTRUCTOR";
		case 452: return "ARRAY_CONSTRUCTOR";
		case 453: return "SECTION_REF";
		case 454: return "VECTOR_SUBSCRIPT";
		case 455: return "SECTION_OPERANDS";
		case 456: return "KEYWORD_ARG";
		case 457: return "OVERLOADED_CALL";
		case 458: return "INTERFACE_REF";
		case 459: return "RENAME_NODE";
		case 460: return "TYPE_NODE";
		case 461: return "PAREN_OP";
		case 462: return "PARAMETER_OP";
		case 463: return "PUBLIC_OP";
		case 464: return "PRIVATE_OP";
		case 465: return "ALLOCATABLE_OP";
		case 466: return "DIMENSION_OP";
		case 467: return "EXTERNAL_OP";
		case 468: return "IN_OP";
		case 469: return "OUT_OP";
		case 470: return "INOUT_OP";
		case 471: return "INTRINSIC_OP";
		case 472: return "POINTER_OP";
		case 473: return "OPTIONAL_OP";
		case 474: return "SAVE_OP";
		case 475: return "TARGET_OP";
		case 476: return "ONLY_NODE";
		case 477: return "LEN_OP";
		case 479: return "TYPE_OP";
		case 480: return "DOTSTAR_OP";	/* C++ .* operator */
		case 481: return "ARROWSTAR_OP";	/* C++ ->* operator */
		case 482: return "FORDECL_OP";	/* C++ for(int i; needs a new op */
		case 483: return "THROW_OP";	/* C++ throw operator */
		case 484: return "PROCESSORS_REF";	/* Fortran M */
		case 485: return "PORT_TYPE_OP";	/* Fortran M */
		case 486: return "INPORT_TYPE_OP";	/* Fortran M */
		case 487: return "OUTPORT_TYPE_OP";	/* Fortran M */
		case 488: return "INPORT_NAME";	/* Fortran M */
		case 489: return "OUTPORT_NAME";	/* Fortran M */
		case 490: return "FROMPORT_NAME";	/* Fortran M */
		case 491: return "TOPORT_NAME";	/* Fortran M */
		case 492: return "IOSTAT_STORE";	/* Fortran M */
		case 493: return "EMPTY_STORE";	/* Fortran M */
		case 494: return "ERR_LABEL";	/* Fortran M */
		case 495: return "END_LABEL";	/* Fortran M */
		case 496: return "PROS_CALL";	/* Fortran M */
		case 497: return "STATIC_OP";     /* F95*/

		case 605	/* DVM-F */ : return "DVM_TASK_REGION_DIR";
		case 606	/* DVM-F */ : return "DVM_END_TASK_REGION_DIR";
		case 607	/* DVM-F */ : return "DVM_ON_DIR";
		case 608	/* DVM-F */ : return "DVM_END_ON_DIR";
		case 609	/* DVM-F */ : return "DVM_TASK_DIR";
		case 610	/* DVM-F */ : return "DVM_MAP_DIR";
		case 611     /* DVM-F */ : return "DVM_PARALLEL_TASK_DIR";
		case 612	/* DVM-F */ : return "DVM_INHERIT_DIR";
		case 613	/* DVM-F */ : return "DVM_INDIRECT_GROUP_DIR";
		case 614	/* DVM-F */ : return "DVM_INDIRECT_ACCESS_DIR";
		case 615	/* DVM-F */ : return "DVM_REMOTE_GROUP_DIR";
		case 616	/* DVM-F */ : return "DVM_RESET_DIR";
		case 617	/* DVM-F */ : return "DVM_PREFETCH_DIR";
		case 618	/* DVM-F */ : return "DVM_OWN_DIR";
		case 619	/* DVM-F */ : return "DVM_HEAP_DIR";
		case 620	/* DVM-F */ : return "DVM_ASYNCID_DIR";
		case 621	/* DVM-F */ : return "DVM_ASYNCHRONOUS_DIR";
		case 622	/* DVM-F */ : return "DVM_ENDASYNCHRONOUS_DIR";
		case 623	/* DVM-F */ : return "DVM_ASYNCWAIT_DIR";
		case 624	/* DVM-F */ : return "DVM_F90_DIR";
		case 625	/* DVM-F */ : return "DVM_BARRIER_DIR";
		case 626	/* F95 */ : return "FORALL_STAT";
		case 627	/* DVM-F */ : return "DVM_CONSISTENT_GROUP_DIR";
		case 628	/* DVM-F */ : return "DVM_CONSISTENT_START_DIR";
		case 629	/* DVM-F */ : return "DVM_CONSISTENT_WAIT_DIR";
		case 630	/* DVM-F */ : return "DVM_CONSISTENT_DIR";
		case 631	/* DVM-F */ : return "DVM_CHECK_DIR";
					case 700: return "DATA_IMPL_DO";     /* Fortran M */
		case 701: return "DATA_ELT";     /* Fortran M */
		case 702: return "DATA_SUBS";     /* Fortran M */
		case 703: return "DATA_RANGE";     /* Fortran M */
		case 704: return "ICON_EXPR";     /* Fortran M */
		case 705: return "BLOCK_OP";     /* DVM-F */
		case 706: return "NEW_SPEC_OP";     /* DVM-F */
		case 707: return "REDUCTION_OP";     /* DVM-F */
		case 708: return "SHADOW_RENEW_OP";     /* DVM-F */
		case 709: return "SHADOW_START_OP";     /* DVM-F */
		case 710: return "SHADOW_WAIT_OP";     /* DVM-F */
		case 711: return "DIAG_OP";     /* DVM-F */
		case 712: return "REMOTE_ACCESS_OP";     /* DVM-F */
		case 713: return "TEMPLATE_OP";     /* DVM-F */
		case 714: return "PROCESSORS_OP";     /* DVM-F */
		case 715: return "DYNAMIC_OP";     /* DVM-F */
		case 716: return "ALIGN_OP";     /* DVM-F */
		case 717: return "DISTRIBUTE_OP";     /* DVM-F */
		case 718: return "SHADOW_OP";     /* DVM-F */
		case 719: return "INDIRECT_ACCESS_OP";     /* DVM-F */
		case 720: return "ACROSS_OP";     /* DVM-F */
		case 721: return "NEW_VALUE_OP";     /* DVM-F */
		case 722: return "SHADOW_COMP_OP";     /* DVM-F */
		case 723: return "STAGE_OP";     /* DVM-F */
		case 724: return "FORALL_OP";     /* F95 */	
		case 725: return "CONSISTENT_OP";     /* DVM-F */
		case 726: return "INTERFACE_OPERATOR";     /* F95 */
		case 727: return "INTERFACE_ASSIGNMENT";     /* F95 */
		case 728: return "VAR_DECL_90";     /* F95 */
		case 729: return "ASSIGNMENT_OP";     /* F95 */
		case 730: return "OPERATOR_OP";     /* F95 */
		case 731: return "KIND_OP";     /* F95 */
		case 732: return "LENGTH_OP";     /* F95 */
		case 733: return "RECURSIVE_OP";    /* F95 */
		case 734: return "ELEMENTAL_OP";    /* F95 */
		case 735: return "PURE_OP";    /* F95 */
		case 736: return "DEFINED_OP";    /* F95 */

		default : return "_unknown_";
	}
}
