########################################################################
# Makefile for Sapfor 2017 
########################################################################

LIBDIR = ../_lib
BINDIR = ../_bin
SRCDIR = ../_src

CXX = g++
CC  = gcc
CFLAGS = -O3 -D__SPF
STD=c++11

REPO_FDVM_BASE      = ../../../../dvm/fdvm/trunk/
REPO_SPF_BASE       = ../_src/
REPO_TRANSFORM_BASE = ../../../transformers/ftransform/trunk/


SAGE_BASE_DIR = $(REPO_FDVM_BASE)Sage/
SAGE_SRC_DIR  = $(SAGE_BASE_DIR)Sage++/
SAGE_SRC_NEW  = $(SAGE_BASE_DIR)lib/newsrc/
SAGE_SRC_OLD  = $(SAGE_BASE_DIR)lib/oldsrc/
SAGE_INCL_DIR = $(SAGE_BASE_DIR)/h
LIB_INCL      = $(SAGE_BASE_DIR)/lib/include

DVMINCLUDE      = $(REPO_FDVM_BASE)/include
PARSER_BASE_DIR = $(REPO_FDVM_BASE)parser/

INLINER_BASE_DIR = $(REPO_FDVM_BASE)InlineExpansion/

TR_COMMON_BASE_DIR = $(REPO_TRANSFORM_BASE)CommonLib/
TR_LIB_BASE_DIR    = $(REPO_TRANSFORM_BASE)SageTransformLib/
TR_UTILS_BASE_DIR  = $(REPO_TRANSFORM_BASE)SageUtils/
TR_SAGE_INCLUDES   = -I$(LIB_INCL) -I$(SAGE_INCL_DIR) -I$(DVMINCLUDE)
all: $(LIBDIR)/trCommonLib.a $(LIBDIR)/trLib.a $(LIBDIR)/trUtils.a $(LIBDIR)/libSage++.a $(LIBDIR)/SageNewSrc.a $(LIBDIR)/SageOldSrc.a $(BINDIR)/Parser $(BINDIR)/Inliner $(BINDIR)/Sapfor

#Make transform common lib
TR_COMMON_OBS = Log.o SageTransformException.o SignalHandling.o Stacktrace.o StringUtils.o
TR_COMMON_INC = -I$(TR_COMMON_BASE_DIR)include/ $(TR_SAGE_INCLUDES) -I$(TR_UTILS_BASE_DIR)include/

$(LIBDIR)/trCommonLib.a: $(TR_COMMON_OBS)
	ar qc $(LIBDIR)/trCommonLib.a $(TR_COMMON_OBS)
Log.o: $(TR_COMMON_BASE_DIR)src/Log.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_COMMON_BASE_DIR)/src/Log.cpp $(TR_COMMON_INC)
SageTransformException.o: $(TR_COMMON_BASE_DIR)src/SageTransformException.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_COMMON_BASE_DIR)/src/SageTransformException.cpp $(TR_COMMON_INC)
SignalHandling.o: $(TR_COMMON_BASE_DIR)src/SignalHandling.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_COMMON_BASE_DIR)/src/SignalHandling.cpp $(TR_COMMON_INC)
Stacktrace.o: $(TR_COMMON_BASE_DIR)src/Stacktrace.cpp 
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_COMMON_BASE_DIR)/src/Stacktrace.cpp $(TR_COMMON_INC)
StringUtils.o: $(TR_COMMON_BASE_DIR)src/StringUtils.cpp 
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_COMMON_BASE_DIR)/src/StringUtils.cpp $(TR_COMMON_INC)
	
#Make transform lib
TR_LIB_OBS = BaseTransform.o LoopCombine.o LoopTransformBreak.o LoopTransformMerge.o LoopTransformSplit.o LoopTransformTighten.o LoopWrapTransform.o \
             StatementOrderTransform.o StatementReorderer.o StatementReshuffler.o StatementsSplitter.o TempArrayTransform.o WriteDearray.o \
			 Dependency.o DependencyInfo.o DependencyInfoGetter.o DependencyUtils.o
			 
TR_LIB_INC = -I$(TR_LIB_BASE_DIR)include/dependency/ -I$(TR_LIB_BASE_DIR)include/ -I$(TR_COMMON_BASE_DIR)include/ -I$(TR_UTILS_BASE_DIR)include/ $(TR_SAGE_INCLUDES) -I$(REPO_SPF_BASE)

$(LIBDIR)/trLib.a: $(TR_LIB_OBS)
	ar qc $(LIBDIR)/trLib.a $(TR_LIB_OBS)
BaseTransform.o: $(TR_LIB_BASE_DIR)src/BaseTransform.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/BaseTransform.cpp $(TR_LIB_INC)
LoopCombine.o: $(TR_LIB_BASE_DIR)src/LoopCombine.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/LoopCombine.cpp $(TR_LIB_INC)
LoopTransformBreak.o: $(TR_LIB_BASE_DIR)src/LoopTransformBreak.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/LoopTransformBreak.cpp $(TR_LIB_INC)
LoopTransformMerge.o: $(TR_LIB_BASE_DIR)src/LoopTransformMerge.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/LoopTransformMerge.cpp $(TR_LIB_INC)
LoopTransformSplit.o: $(TR_LIB_BASE_DIR)src/LoopTransformSplit.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/LoopTransformSplit.cpp $(TR_LIB_INC)
LoopTransformTighten.o: $(TR_LIB_BASE_DIR)src/LoopTransformTighten.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/LoopTransformTighten.cpp $(TR_LIB_INC)
LoopWrapTransform.o: $(TR_LIB_BASE_DIR)src/LoopWrapTransform.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/LoopWrapTransform.cpp $(TR_LIB_INC)
StatementOrderTransform.o: $(TR_LIB_BASE_DIR)src/StatementOrderTransform.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/StatementOrderTransform.cpp $(TR_LIB_INC)
StatementReorderer.o: $(TR_LIB_BASE_DIR)src/StatementReorderer.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/StatementReorderer.cpp $(TR_LIB_INC)
StatementReshuffler.o: $(TR_LIB_BASE_DIR)src/StatementReshuffler.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/StatementReshuffler.cpp $(TR_LIB_INC)
StatementsSplitter.o: $(TR_LIB_BASE_DIR)src/StatementsSplitter.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/StatementsSplitter.cpp $(TR_LIB_INC)
TempArrayTransform.o: $(TR_LIB_BASE_DIR)src/TempArrayTransform.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/TempArrayTransform.cpp $(TR_LIB_INC)
WriteDearray.o: $(TR_LIB_BASE_DIR)src/WriteDearray.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/WriteDearray.cpp $(TR_LIB_INC)
Dependency.o: $(TR_LIB_BASE_DIR)src/dependency/Dependency.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/dependency/Dependency.cpp $(TR_LIB_INC)
DependencyInfo.o: $(TR_LIB_BASE_DIR)src/dependency/DependencyInfo.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/dependency/DependencyInfo.cpp $(TR_LIB_INC)
DependencyInfoGetter.o: $(TR_LIB_BASE_DIR)src/dependency/DependencyInfoGetter.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/dependency/DependencyInfoGetter.cpp $(TR_LIB_INC)
DependencyUtils.o: $(TR_LIB_BASE_DIR)src/dependency/DependencyUtils.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_LIB_BASE_DIR)/src/dependency/DependencyUtils.cpp $(TR_LIB_INC)
	
#Make transform utils
TR_UTILS_OBS = decodeStmtVariant.o SageTransformUtils.o SageUtils.o LineReorderRecord.o LineReorderer.o
			 
TR_UTILS_INC = -I$(TR_UTILS_BASE_DIR)include/ $(TR_SAGE_INCLUDES) -I$(TR_COMMON_BASE_DIR)include/

$(LIBDIR)/trUtils.a: $(TR_UTILS_OBS)
	ar qc $(LIBDIR)/trUtils.a $(TR_UTILS_OBS)

decodeStmtVariant.o: $(TR_UTILS_BASE_DIR)src/decodeStmtVariant.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_UTILS_BASE_DIR)/src/decodeStmtVariant.cpp $(TR_UTILS_INC)
SageTransformUtils.o: $(TR_UTILS_BASE_DIR)src/SageTransformUtils.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_UTILS_BASE_DIR)/src/SageTransformUtils.cpp $(TR_UTILS_INC)
SageUtils.o: $(TR_UTILS_BASE_DIR)src/SageUtils.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_UTILS_BASE_DIR)/src/SageUtils.cpp $(TR_UTILS_INC)
LineReorderRecord.o: $(TR_UTILS_BASE_DIR)src/LineReorderRecord.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_UTILS_BASE_DIR)/src/LineReorderRecord.cpp $(TR_UTILS_INC)
LineReorderer.o: $(TR_UTILS_BASE_DIR)src/LineReorderer.cpp
	$(CXX) $(CFLAGS) -c -std=$(STD)  $(TR_UTILS_BASE_DIR)/src/LineReorderer.cpp $(TR_UTILS_INC)

#Make SAGE++
libSage++.o: $(SAGE_SRC_DIR)libSage++.cpp $(LIB_INCL)/macro.h $(LIB_INCL)/bif_node.def $(LIB_INCL)/type.def $(LIB_INCL)/symb.def $(LIB_INCL)/libSage++.h
	$(CXX) $(CFLAGS)  -c $(SAGE_SRC_DIR)libSage++.cpp -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
$(LIBDIR)/libSage++.a: libSage++.o
	ar qc $(LIBDIR)/libSage++.a libSage++.o
	
#Make SAGE newsrc
low_level.o: $(SAGE_SRC_NEW)low_level.c $(LIB_INCL)/macro.h $(LIB_INCL)/bif_node.def $(LIB_INCL)/type.def  $(LIB_INCL)/symb.def 
	$(CC) $(CFLAGS) -c -DSYS5  $(SAGE_SRC_NEW)low_level.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
unparse.o:  $(SAGE_SRC_NEW)unparse.c $(LIB_INCL)/macro.h $(LIB_INCL)/bif_node.def $(LIB_INCL)/type.def  $(LIB_INCL)/symb.def  $(LIB_INCL)/unparse.def $(LIB_INCL)/unparseC++.def
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_NEW)unparse.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
annotate.tab.o: $(SAGE_SRC_NEW)annotate.tab.c $(LIB_INCL)/macro.h $(LIB_INCL)/bif_node.def $(LIB_INCL)/type.def  $(LIB_INCL)/symb.def 
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_NEW)annotate.tab.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
comments.o: $(SAGE_SRC_NEW)comments.c $(LIB_INCL)/macro.h $(LIB_INCL)/bif_node.def $(LIB_INCL)/type.def  $(LIB_INCL)/symb.def 
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_NEW)comments.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
toolsann.o: $(SAGE_SRC_NEW)toolsann.c $(LIB_INCL)/macro.h $(LIB_INCL)/bif_node.def $(LIB_INCL)/type.def  $(LIB_INCL)/symb.def 
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_NEW)toolsann.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)

$(LIBDIR)/SageNewSrc.a: low_level.o  unparse.o annotate.tab.o comments.o toolsann.o $(LIB_INCL)/macro.h $(LIB_INCL)/bif_node.def $(LIB_INCL)/type.def  $(LIB_INCL)/symb.def  
	ar qc $(LIBDIR)/SageNewSrc.a low_level.o unparse.o annotate.tab.o comments.o toolsann.o

#Make SAGE oldsrc
OLD_SRC_OBJS = anal_ind.o  db.o  db_unp.o db_unp_vpc.o   dbutils.o  garb_coll.o glob_anal.o  ker_fun.o  \
			   list.o make_nodes.o  mod_ref.o  ndeps.o readnodes.o  sets.o  setutils.o symb_alg.o  writenodes.o 

H = $(SAGE_INCL_DIR)
anal_ind.o: $(SAGE_SRC_OLD)anal_ind.c   $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)anal_ind.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
db.o: $(SAGE_SRC_OLD)db.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)db.c  -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
db_unp.o: $(SAGE_SRC_OLD)db_unp.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h 
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)db_unp.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
db_unp_vpc.o: $(SAGE_SRC_OLD)db_unp_vpc.c $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h $(H)/db.h $(H)/vparse.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)db_unp_vpc.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
dbutils.o: $(SAGE_SRC_OLD)dbutils.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)dbutils.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
garb_coll.o: $(SAGE_SRC_OLD)garb_coll.c  $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)garb_coll.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
glob_anal.o: $(SAGE_SRC_OLD)glob_anal.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)glob_anal.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
ker_fun.o:  $(SAGE_SRC_OLD)ker_fun.c $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)ker_fun.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
list.o: $(SAGE_SRC_OLD)list.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h $(H)/list.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)list.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
make_nodes.o: $(SAGE_SRC_OLD)make_nodes.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)make_nodes.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
mod_ref.o: $(SAGE_SRC_OLD)mod_ref.c $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h $(H)/vparse.h $(H)/db.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)mod_ref.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
ndeps.o: $(SAGE_SRC_OLD)ndeps.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)ndeps.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
readnodes.o: $(SAGE_SRC_OLD)readnodes.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h $(H)/dep_str.h $(H)/dep.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)readnodes.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
sets.o: $(SAGE_SRC_OLD)sets.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)sets.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
setutils.o: $(SAGE_SRC_OLD)setutils.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)setutils.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
symb_alg.o: $(SAGE_SRC_OLD)symb_alg.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)symb_alg.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
writenodes.o: $(SAGE_SRC_OLD)writenodes.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h $(H)/dep_str.h $(H)/dep.h
	$(CC) $(CFLAGS) -c -DSYS5 $(SAGE_SRC_OLD)writenodes.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
	
$(LIBDIR)/SageOldSrc.a: $(OLD_SRC_OBJS)
	ar qc $(LIBDIR)/SageOldSrc.a $(OLD_SRC_OBJS)
	
#Make Parser
PARSER_OBJS = cftn.o errors.o hash.o init.o lexfdvm.o lists.o misc.o stat.o types.o gram1.tab.o sym.o low_hpf.o unparse_hpf.o
$(BINDIR)/Parser: $(PARSER_OBJS) $(LIBDIR)/SageOldSrc.a
	$(CXX) -o $(BINDIR)/Parser $(PARSER_OBJS) $(LIBDIR)/SageOldSrc.a
	
cftn.o: $(PARSER_BASE_DIR)cftn.c $(H)/db.h $(H)/defs.h $(H)/tag $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)cftn.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
errors.o: $(PARSER_BASE_DIR)errors.c $(H)/defs.h $(H)/tag $(H)/symb.h $(DVMINCLUDE)/extern.h $(H)/db.h $(H)/bif.h $(H)/ll.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)errors.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
hash.o: $(PARSER_BASE_DIR)hash.c $(H)/defs.h $(H)/symb.h $(H)/defines.h $(DVMINCLUDE)/extern.h $(H)/db.h $(H)/bif.h $(H)/ll.h $(H)/sets.h $(H)/tag 
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)hash.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
init.o: $(PARSER_BASE_DIR)init.c $(DVMINCLUDE)/inc.h $(H)/defs.h $(H)/bif.h $(H)/defines.h $(H)/ll.h $(H)/symb.h $(H)/sets.h $(H)/db.h $(H)/tag
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)init.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
lexfdvm.o: $(PARSER_BASE_DIR)lexfdvm.c $(DVMINCLUDE)/extern.h
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)lexfdvm.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
lists.o: $(PARSER_BASE_DIR)lists.c $(H)/defs.h $(H)/ll.h $(H)/symb.h $(H)/bif.h
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)lists.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
misc.o: $(PARSER_BASE_DIR)misc.c $(H)/defs.h $(H)/tag $(H)/defines.h $(H)/db.h $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)misc.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
stat.o: $(PARSER_BASE_DIR)stat.c $(H)/defs.h $(H)/bif.h $(H)/ll.h $(H)/symb.h $(H)/sets.h $(H)/defines.h $(DVMINCLUDE)/extern.h
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)stat.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
sym.o: $(PARSER_BASE_DIR)sym.c $(H)/defs.h $(H)/tag $(H)/symb.h $(H)/defines.h $(H)/bif.h $(DVMINCLUDE)/extern.h $(H)/db.h $(H)/ll.h $(H)/sets.h $(DVMINCLUDE)/fdvm.h
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)sym.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
types.o: $(PARSER_BASE_DIR)types.c $(H)/defs.h $(H)/ll.h $(H)/symb.h
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)types.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
low_hpf.o: $(PARSER_BASE_DIR)low_hpf.c $(DVMINCLUDE)/dvm_tag.h $(TOOLBOX_HDR)
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)low_hpf.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
unparse_hpf.o: $(PARSER_BASE_DIR)unparse_hpf.c $(DVMINCLUDE)/dvm_tag.h $(TOOLBOX_HDR) $(DVMINCLUDE)/unparse.hpf
	$(CC) $(CFLAGS) -c -DSYS5  $(PARSER_BASE_DIR)unparse_hpf.c -I$(SAGE_INCL_DIR) -I$(LIB_INCL) -I$(DVMINCLUDE)
gram1.tab.o: $(PARSER_BASE_DIR)gram1.tab.c
	$(CC) $(CFLAGS) -c -DSYS5 -DYYDEBUG  $(PARSER_BASE_DIR)gram1.tab.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)

#Make Inliner
$(BINDIR)/Inliner: inl_exp.o inliner.o hlp.o $(LIBDIR)/libSage++.a $(LIBDIR)/SageNewSrc.a $(LIBDIR)/SageOldSrc.a
	$(CXX) -o $(BINDIR)/Inliner inl_exp.o inliner.o hlp.o $(LIBDIR)/libSage++.a $(LIBDIR)/SageNewSrc.a $(LIBDIR)/SageOldSrc.a
	
inl_exp.o: $(INLINER_BASE_DIR)inl_exp.cpp $(INLINER_BASE_DIR)inline.h
	$(CXX) $(CFLAGS) -std=$(STD)  -c $(INLINER_BASE_DIR)inl_exp.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
inliner.o: $(INLINER_BASE_DIR)inliner.cpp $(INLINER_BASE_DIR)inline.h
	$(CXX) $(CFLAGS) -std=$(STD)  -c $(INLINER_BASE_DIR)inliner.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
hlp.o: $(INLINER_BASE_DIR)hlp.cpp $(INLINER_BASE_DIR)inline.h
	$(CXX) $(CFLAGS) -std=$(STD)  -c $(INLINER_BASE_DIR)hlp.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)

#Make Sapfor
SAPFOR_OBJ = private_analyzer.o utils.o SgUtils.o transforms.o CorrectVarDecl.o IncludeChecker.o LoopChecker.o ParRegions.o \
             enddo_loop_converter.o array_assign_to_loop.o allocations_prepoc.o directive_creator.o insert_directive.o loop_analyzer.o spf_directive_preproc.o \
			 graph_loops.o graph_loops_base.o graph_calls.o expr_transform.o CreateDistributionDirs.o DvmhDirective.o DvmhDirectiveBase.o DirectiveAnalyzer.o \
			 acc_analyzer.o acc_data.o calls.o acc_utilities.o directive_parser.o GraphCSR.o Distribution.o Cycle.o \
			 annotationDriver.o arrayRef.o computeInducVar.o constanteProp.o  controlFlow.o defUse.o dependence.o depGraph.o \
			 depInterface.o flowAnalysis.o intrinsic.o invariant.o loopTransform.o set.o \
			 add-assert.o affine.o cover.o ddomega.o ddomega-build.o ddomega-use.o debug.o ip.o kill.o refine.o sagedriver.o \
			 dep_analyzer.o remote_access.o VerifySageStructures.o loop_transform.o PredictScheme.o

$(BINDIR)/Sapfor: $(SAPFOR_OBJ) $(LIBDIR)/libSage++.a $(LIBDIR)/SageNewSrc.a $(LIBDIR)/SageOldSrc.a
	$(CXX) -fopenmp -o $(BINDIR)/Sapfor $(SAPFOR_OBJ) $(LIBDIR)/libSage++.a $(LIBDIR)/SageNewSrc.a $(LIBDIR)/SageOldSrc.a $(LIBDIR)/trLib.a $(LIBDIR)/trUtils.a $(LIBDIR)/trCommonLib.a

utils.o: $(REPO_SPF_BASE)utils.cpp $(REPO_SPF_BASE)errors.h $(REPO_SPF_BASE)utils.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)utils.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
SgUtils.o: $(REPO_SPF_BASE)SgUtils.cpp $(REPO_SPF_BASE)errors.h $(REPO_SPF_BASE)utils.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SgUtils.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
directive_parser.o: $(REPO_SPF_BASE)directive_parser.cpp $(REPO_SPF_BASE)directive_parser.h $(REPO_SPF_BASE)utils.h $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)directive_parser.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)	
transforms.o: $(REPO_SPF_BASE)transforms.cpp $(REPO_SPF_BASE)errors.h $(REPO_SPF_BASE)utils.h $(REPO_SPF_BASE)LoopConverter/enddo_loop_converter.h \
			  $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.h $(REPO_SPF_BASE)GraphCall/graph_calls.h $(REPO_SPF_BASE)GraphLoop/graph_loops.h \
			  $(REPO_SPF_BASE)DirectiveAnalyzer/DirectiveAnalyzer.h $(REPO_SPF_BASE)VerificationCode/verifications.h $(REPO_SPF_BASE)Distribution/CreateDistributionDirs.h \
			  $(REPO_SPF_BASE)PrivateAnalyzer/private_analyzer.h $(REPO_SPF_BASE)transform.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)transforms.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL) $(TR_LIB_INC)
CorrectVarDecl.o: $(REPO_SPF_BASE)VerificationCode/CorrectVarDecl.cpp $(REPO_SPF_BASE)VerificationCode/verifications.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)VerificationCode/CorrectVarDecl.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
IncludeChecker.o: $(REPO_SPF_BASE)VerificationCode/IncludeChecker.cpp $(REPO_SPF_BASE)VerificationCode/verifications.h  $(REPO_SPF_BASE)utils.h  $(REPO_SPF_BASE)Distribution/DvmhDirective.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)VerificationCode/IncludeChecker.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
LoopChecker.o: $(REPO_SPF_BASE)VerificationCode/LoopChecker.cpp $(REPO_SPF_BASE)VerificationCode/verifications.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)VerificationCode/LoopChecker.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
VerifySageStructures.o: $(REPO_SPF_BASE)VerificationCode/VerifySageStructures.cpp $(REPO_SPF_BASE)VerificationCode/verifications.h $(REPO_SPF_BASE)utils.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)VerificationCode/VerifySageStructures.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
private_analyzer.o: $(REPO_SPF_BASE)PrivateAnalyzer/private_analyzer.cpp $(REPO_SPF_BASE)PrivateAnalyzer/private_analyzer.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)PrivateAnalyzer/private_analyzer.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
acc_analyzer.o: $(REPO_FDVM_BASE)fdvm/acc_analyzer.cpp 
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_FDVM_BASE)fdvm/acc_analyzer.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)	
acc_data.o: $(REPO_FDVM_BASE)fdvm/acc_data.cpp 
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_FDVM_BASE)fdvm/acc_data.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
acc_utilities.o: $(REPO_FDVM_BASE)fdvm/acc_utilities.cpp
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_FDVM_BASE)fdvm/acc_utilities.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
calls.o: $(REPO_FDVM_BASE)fdvm/calls.cpp 
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_FDVM_BASE)fdvm/calls.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
ParRegions.o: $(REPO_SPF_BASE)ParallelizationRegions/ParRegions.cpp $(REPO_SPF_BASE)ParallelizationRegions/ParRegions.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)ParallelizationRegions/ParRegions.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
enddo_loop_converter.o: $(REPO_SPF_BASE)LoopConverter/enddo_loop_converter.cpp $(REPO_SPF_BASE)LoopConverter/enddo_loop_converter.h $(REPO_SPF_BASE)errors.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopConverter/enddo_loop_converter.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
array_assign_to_loop.o: $(REPO_SPF_BASE)LoopConverter/array_assign_to_loop.cpp $(REPO_SPF_BASE)LoopConverter/array_assign_to_loop.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopConverter/array_assign_to_loop.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
loop_transform.o: $(REPO_SPF_BASE)LoopConverter/loop_transform.cpp $(REPO_SPF_BASE)LoopConverter/loop_transform.h $(REPO_SPF_BASE)errors.h $(REPO_SPF_BASE)GraphLoop/graph_loops.h 
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopConverter/loop_transform.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL) $(TR_LIB_INC)
CreateInterTree.o: $(REPO_SPF_BASE)CreateInterTree/CreateInterTree.cpp $(REPO_SPF_BASE)CreateInterTree/CreateInterTree.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)CreateInterTree/CreateInterTree.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL) $(TR_LIB_INC)

allocations_prepoc.o: $(REPO_SPF_BASE)LoopAnalyzer/allocations_prepoc.cpp $(REPO_SPF_BASE)utils.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopAnalyzer/allocations_prepoc.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
directive_creator.o: $(REPO_SPF_BASE)LoopAnalyzer/directive_creator.cpp $(REPO_SPF_BASE)ParallelizationRegions/ParRegions.h \
					 $(REPO_SPF_BASE)Distribution/GraphCSR.h $(REPO_SPF_BASE)Distribution/Arrays.h $(REPO_SPF_BASE)Distribution/Distribution.h \
					 $(REPO_SPF_BASE)errors.h $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.h $(REPO_SPF_BASE)directive_parser.h $(REPO_SPF_BASE)utils.h \
					 $(REPO_SPF_BASE)transform.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopAnalyzer/directive_creator.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL) $(TR_LIB_INC)
insert_directive.o: $(REPO_SPF_BASE)LoopAnalyzer/insert_directive.cpp $(REPO_SPF_BASE)Distribution/GraphCSR.h $(REPO_SPF_BASE)Distribution/Arrays.h \
					$(REPO_SPF_BASE)Distribution/Distribution.h $(REPO_SPF_BASE)Distribution/DvmhDirective.h $(REPO_SPF_BASE)errors.h \
					$(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.h $(REPO_SPF_BASE)directive_parser.h $(REPO_SPF_BASE)utils.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopAnalyzer/insert_directive.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
loop_analyzer.o: $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.cpp $(REPO_SPF_BASE)Distribution/GraphCSR.h $(REPO_SPF_BASE)Distribution/Arrays.h \
				 $(REPO_SPF_BASE)Distribution/Distribution.h $(REPO_SPF_BASE)ParallelizationRegions/ParRegions.h $(REPO_SPF_BASE)errors.h $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.h \
				 $(REPO_SPF_BASE)directive_parser.h $(REPO_SPF_BASE)utils.h $(REPO_SPF_BASE)GraphCall/graph_calls.h $(REPO_SPF_BASE)ExpressionTransform/expr_transform.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)	
remote_access.o: $(REPO_SPF_BASE)LoopAnalyzer/remote_access.cpp $(REPO_SPF_BASE)Distribution/Arrays.h \
				 $(REPO_SPF_BASE)errors.h $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.h \
				 $(REPO_SPF_BASE)utils.h $(REPO_SPF_BASE)GraphCall/graph_calls.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopAnalyzer/remote_access.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
dep_analyzer.o: $(REPO_SPF_BASE)LoopAnalyzer/dep_analyzer.cpp $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.h $(REPO_SPF_BASE)utils.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopAnalyzer/dep_analyzer.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)	
spf_directive_preproc.o: $(REPO_SPF_BASE)LoopAnalyzer/spf_directive_preproc.cpp
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)LoopAnalyzer/spf_directive_preproc.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
graph_loops.o: $(REPO_SPF_BASE)GraphLoop/graph_loops.cpp $(REPO_SPF_BASE)GraphLoop/graph_loops.h $(REPO_SPF_BASE)GraphCall/graph_calls.h \
			   $(REPO_SPF_BASE)Distribution/GraphCSR.h $(REPO_SPF_BASE)Distribution/Arrays.h $(REPO_SPF_BASE)Distribution/Distribution.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)GraphLoop/graph_loops.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
graph_loops_base.o: $(REPO_SPF_BASE)GraphLoop/graph_loops_base.cpp $(REPO_SPF_BASE)GraphLoop/graph_loops.h $(REPO_SPF_BASE)GraphCall/graph_calls.h \
			   $(REPO_SPF_BASE)Distribution/GraphCSR.h $(REPO_SPF_BASE)Distribution/Arrays.h $(REPO_SPF_BASE)Distribution/Distribution.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)GraphLoop/graph_loops_base.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
PredictScheme.o: $(REPO_SPF_BASE)Predictor/PredictScheme.cpp $(REPO_SPF_BASE)Predictor/PredictScheme.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)Predictor/PredictScheme.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
graph_calls.o: $(REPO_SPF_BASE)GraphCall/graph_calls.cpp $(REPO_SPF_BASE)GraphLoop/graph_loops.h $(REPO_SPF_BASE)GraphCall/graph_calls.h $(REPO_SPF_BASE)/directive_parser.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)GraphCall/graph_calls.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
expr_transform.o: $(REPO_SPF_BASE)ExpressionTransform/expr_transform.cpp
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)ExpressionTransform/expr_transform.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
CreateDistributionDirs.o: $(REPO_SPF_BASE)Distribution/CreateDistributionDirs.cpp  $(REPO_SPF_BASE)Distribution/Distribution.h  $(REPO_SPF_BASE)Distribution/GraphCSR.h \
						  $(REPO_SPF_BASE)Distribution/Arrays.h  $(REPO_SPF_BASE)errors.h  $(REPO_SPF_BASE)GraphLoop/graph_loops.h  $(REPO_SPF_BASE)LoopAnalyzer/loop_analyzer.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)Distribution/CreateDistributionDirs.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
DvmhDirective.o: $(REPO_SPF_BASE)Distribution/DvmhDirective.cpp $(REPO_SPF_BASE)Distribution/DvmhDirective.h $(REPO_SPF_BASE)utils.h 
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)Distribution/DvmhDirective.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
DvmhDirectiveBase.o: $(REPO_SPF_BASE)Distribution/DvmhDirectiveBase.cpp $(REPO_SPF_BASE)Distribution/DvmhDirectiveBase.h $(REPO_SPF_BASE)utils.h 
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)Distribution/DvmhDirectiveBase.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
DirectiveAnalyzer.o: $(REPO_SPF_BASE)DirectiveAnalyzer/DirectiveAnalyzer.cpp $(REPO_SPF_BASE)Distribution/DvmhDirective.h $(REPO_SPF_BASE)GraphLoop/graph_loops.h \
					 $(REPO_SPF_BASE)DirectiveAnalyzer/DirectiveAnalyzer.h $(REPO_SPF_BASE)utils.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)DirectiveAnalyzer/DirectiveAnalyzer.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
Cycle.o: $(REPO_SPF_BASE)Distribution/Cycle.cpp $(REPO_SPF_BASE)Distribution/Cycle.h $(REPO_SPF_BASE)Distribution/DvmhDirective.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)Distribution/Cycle.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)	
Distribution.o: $(REPO_SPF_BASE)Distribution/Distribution.cpp $(REPO_SPF_BASE)Distribution/Distribution.h $(REPO_SPF_BASE)Distribution/DvmhDirective.h \
				$(REPO_SPF_BASE)utils.h $(REPO_SPF_BASE)Distribution/GraphCSR.h $(REPO_SPF_BASE)Distribution/Arrays.h $(REPO_SPF_BASE)Distribution/Array.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)Distribution/Distribution.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)	
GraphCSR.o: $(REPO_SPF_BASE)Distribution/GraphCSR.cpp $(REPO_SPF_BASE)Distribution/GraphCSR.h $(REPO_SPF_BASE)Distribution/DvmhDirective.h \
				$(REPO_SPF_BASE)utils.h $(REPO_SPF_BASE)errors.h $(REPO_SPF_BASE)Distribution/Arrays.h $(REPO_SPF_BASE)Distribution/Array.h \
				$(REPO_SPF_BASE)Distribution/Cycle.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)Distribution/GraphCSR.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)	
	
annotationDriver.o: $(REPO_SPF_BASE)SageAnalysisTool/annotationDriver.cpp $(REPO_SPF_BASE)SageAnalysisTool/annotationDriver.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/annotationDriver.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
arrayRef.o: $(REPO_SPF_BASE)SageAnalysisTool/arrayRef.cpp $(REPO_SPF_BASE)SageAnalysisTool/arrayRef.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/arrayRef.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
computeInducVar.o: $(REPO_SPF_BASE)SageAnalysisTool/computeInducVar.cpp $(REPO_SPF_BASE)SageAnalysisTool/set.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/computeInducVar.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
constanteProp.o: $(REPO_SPF_BASE)SageAnalysisTool/constanteProp.cpp $(REPO_SPF_BASE)SageAnalysisTool/set.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/constanteProp.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
controlFlow.o: $(REPO_SPF_BASE)SageAnalysisTool/controlFlow.cpp
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/controlFlow.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
defUse.o: $(REPO_SPF_BASE)SageAnalysisTool/defUse.cpp $(REPO_SPF_BASE)SageAnalysisTool/set.h 
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/defUse.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
dependence.o: $(REPO_SPF_BASE)SageAnalysisTool/dependence.cpp $(REPO_SPF_BASE)SageAnalysisTool/set.h $(REPO_SPF_BASE)SageAnalysisTool/dependence.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/dependence.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
depGraph.o: $(REPO_SPF_BASE)SageAnalysisTool/depGraph.cpp
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/depGraph.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
depInterface.o: $(REPO_SPF_BASE)SageAnalysisTool/depInterface.cpp
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/depInterface.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
flowAnalysis.o: $(REPO_SPF_BASE)SageAnalysisTool/flowAnalysis.cpp
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/flowAnalysis.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
intrinsic.o: $(REPO_SPF_BASE)SageAnalysisTool/intrinsic.cpp $(REPO_SPF_BASE)SageAnalysisTool/intrinsic.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/intrinsic.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
invariant.o: $(REPO_SPF_BASE)SageAnalysisTool/invariant.cpp $(REPO_SPF_BASE)SageAnalysisTool/set.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/invariant.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
loopTransform.o: $(REPO_SPF_BASE)SageAnalysisTool/loopTransform.cpp $(REPO_SPF_BASE)SageAnalysisTool/set.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/loopTransform.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
set.o: $(REPO_SPF_BASE)SageAnalysisTool/set.cpp $(REPO_SPF_BASE)SageAnalysisTool/set.h
	$(CXX) $(CFLAGS) -c  -std=$(STD) $(REPO_SPF_BASE)SageAnalysisTool/set.cpp -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
	
add-assert.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/add-assert.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/add-assert.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
affine.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/affine.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/affine.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
cover.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/cover.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/cover.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
ddomega.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/ddomega.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/ddomega.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
ddomega-build.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/ddomega-build.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/ddomega-build.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
ddomega-use.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/ddomega-use.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/ddomega-use.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
debug.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/debug.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/debug.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
ip.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/ip.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/ip.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
kill.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/kill.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/kill.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
refine.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/refine.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/refine.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
sagedriver.o: $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/sagedriver.c
	$(CC) $(CFLAGS) -c  $(REPO_SPF_BASE)SageAnalysisTool/OmegaForSage/sagedriver.c -I$(DVMINCLUDE) -I$(SAGE_INCL_DIR) -I$(LIB_INCL)
	
clean:
	rm -rf *.o

cleanall:
	rm -rf *.o ../_lib/*.a
