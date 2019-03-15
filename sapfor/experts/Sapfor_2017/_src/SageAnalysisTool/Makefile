#######################################################################
##                  pC++/Sage++  Copyright (C) 1993                  ##
##  Indiana University  University of Oregon  University of Rennes   ##
#######################################################################
 
SAGEROOT = ../../..
CONFIG_ARCH=default

LIBDIR = $(SAGEROOT)/lib/$(CONFIG_ARCH)
LIBINCLUDE = $(SAGEROOT)/lib/include
HINCLUDE = $(SAGEROOT)/h
INSTALLDEST = $(SAGEROOT)/bin/$(CONFIG_ARCH)
INSTALL = /bin/cp

#HP-ALLOCA#LDLIBS  = -lPW#ENDIF#
#HP_CFLAGS#CEXTRA = -Aa#ENDIF#

CC = gcc
#USE_CC#CC=cc#ENDIF#

CXX = g++
#USE_CFRONT#CXX=CC#ENDIF#

LOADER = $(CXX)

INCLUDE = -I$(LIBINCLUDE) -I$(HINCLUDE) -I./OmegaForSage/include

CFLAGS	= $(INCLUDE) -g # $(CEXTRA)
LDFLAGS	= 

LIBS =
#LIBS = $(LIBDIR)/libann.a $(LIBDIR)/libsage.a $(LIBDIR)/libdb.a $(LIBDIR)/libSage++.a

OMEGATEST_OBJ       = OmegaForSage/add-assert.o OmegaForSage/cover.o  OmegaForSage/ddomega-build.o OmegaForSage/ddomega.o  OmegaForSage/kill.o OmegaForSage/affine.o  OmegaForSage/sagedriver.o OmegaForSage/ddomega-use.o OmegaForSage/debug.o  OmegaForSage/ip.o  OmegaForSage/refine.o

HFILE = annotationDriver.h constanteSet.h depGraph.h inducVar.h set.h arrayRef.h definitionSet.h dependence.h intrinsic.h depInterface.h definesValues.h


PROGRAM = libDep.a

OBJS =  set.o controlFlow.o flowAnalysis.o defUse.o  constanteProp.o computeInducVar.o arrayRef.o dependence.o invariant.o depGraph.o intrinsic.o loopTransform.o annotationDriver.o depInterface.o

SRCS =  set.C controlFlow.C flowAnalysis.C defUse.C constanteProp.C computeInducVar.C arrayRef.C dependence.C invariant.C depGraph.C intrinsic.C loopTransform.C annotationDriver.C depInterface.C




all:	$(PROGRAM)

$(PROGRAM): $(OBJS)
	/bin/rm -f libDep.a
	ar qc $(PROGRAM) $(OBJS) $(LIBS) $(OMEGATEST_OBJ) 
	ranlib libDep.a

set.o: set.C $(HFILE)
	$(CXX) $(CFLAGS) -c set.C

controlFlow.o: controlFlow.C $(HFILE)
	$(CXX) $(CFLAGS) -c controlFlow.C

flowAnalysis.o: flowAnalysis.C $(HFILE)
	$(CXX) $(CFLAGS) -c flowAnalysis.C

defUse.o: defUse.C $(HFILE)
	$(CXX) $(CFLAGS) -c defUse.C

constanteProp.o: constanteProp.C $(HFILE)
	$(CXX) $(CFLAGS) -c constanteProp.C

computeInducVar.o: computeInducVar.C $(HFILE)
	$(CXX) $(CFLAGS) -c computeInducVar.C

arrayRef.o: arrayRef.C $(HFILE)
	$(CXX) $(CFLAGS) -c arrayRef.C

dependence.o: dependence.C $(HFILE)
	$(CXX) $(CFLAGS) -c dependence.C

invariant.o: invariant.C $(HFILE)
	$(CXX) $(CFLAGS) -c invariant.C

depGraph.o: depGraph.C $(HFILE)
	$(CXX) $(CFLAGS) -c depGraph.C

intrinsic.o: intrinsic.C $(HFILE)
	$(CXX) $(CFLAGS) -c intrinsic.C


loopTransform.o: loopTransform.C $(HFILE)
	$(CXX) $(CFLAGS) -c loopTransform.C

annotationDriver.o :  annotationDriver.C $(HFILE)
	$(CXX) $(CFLAGS) -c annotationDriver.C

depInterface.o :  depInterface.C $(HFILE)
	$(CXX) $(CFLAGS) -c depInterface.C

clean:
	/bin/rm -f *.o *.dep a.out libDep.a


