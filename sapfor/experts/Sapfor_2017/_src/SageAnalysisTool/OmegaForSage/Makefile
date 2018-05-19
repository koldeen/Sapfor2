# in maple_interface.c include vfork.h
#SUN#CEXTRA=-DSUN=1

# Directory where sigma is installed (used to find include files and libraries)
# DEFINE sigma_prefix as the path to the directory containing  sigma  
sigma_prefix = ../../../sage/Beta/sigma
sigma_lib = $(sigma_prefix)/lib

# Directory where tool box is installed
# DEFINE sigma_prefix as the path to the directory containing  sigma toolc++
toolc++_prefix = .

# Directory in which to put toolc++ library 
toolc++_libdir = .
# Directory in which include file can be found
toolc++_include = .

# 
CC      = gcc
INCLUDE = -I./include -I.
# -w don't issue warning now.
CFLAGS	= $(INCLUDE) -g 
LDFLAGS	= 

OMEGA_SRC	=  add-assert.c cover.c  ddomega-build.c ddomega.c  kill.c affine.c  sagedriver.c ddomega-use.c debug.c  ip.c  refine.c

OMEGA_HDR     = ./include/add-assert.h ./include/ddomega-use.h ./include/kill.h ./include/refine.h ./include/affine.h  ./include/ddomega.h  ./include/cover.h ./include/debug.h ./include/lang-interf.h ./include/ddomega-build.h  ./include/ip.h ./include/portable.h


OMEGA_OBJ	=   add-assert.o cover.o  ddomega-build.o ddomega.o  kill.o affine.o  sagedriver.o ddomega-use.o debug.o  ip.o  refine.o

testq: $(OMEGA_OBJ) 
#	$(CC)  $(OMEGA_OBJ) -o testdebug  -lm -lcurses -ltermcap


add-assert.o : $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c add-assert.c
cover.o : $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c cover.c
ddomega-build.o : $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c ddomega-build.c
ddomega.o: $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c ddomega.c  
kill.o : $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c kill.c
affine.o : $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c affine.c
sagedriver.o : $(OMEGA_HDR)  sagedriver.c
	$(CC) $(CFLAGS) -c sagedriver.c
ddomega-use.o : $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c ddomega-use.c
debug.o: $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c debug.c
ip.o : $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c ip.c
refine.o: $(OMEGA_HDR) 
	$(CC) $(CFLAGS) -c refine.c

clean:
	rm -rf $(OMEGA_OBJ) testdebug 


