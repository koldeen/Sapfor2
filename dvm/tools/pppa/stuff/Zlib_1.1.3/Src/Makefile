.KEEP_STATE:
#############################################################################
#                                                                           #
#                                   RATER                                   #
#                                                                           #
#############################################################################

LIB	    = libzlib.a

INC_DIR = -I../Include

COPT    = -g -w $(INC_DIR) -DP_DEBUG
LINK	= ar r 

.SUFFIXES: .o .cpp
.cpp.o:
	$(CXX) -c $(COPT) $*.cpp

MODULES  = \
	adler32.o compress.o crc32.o gzio.o uncompr.o deflate.o trees.o \
	zutil.o inflate.o infblock.o inftrees.o infcodes.o infutil.o inffast.o

################################## RATER ##################################

all: $(LIB)

$(LIB): $(MODULES) 
	$(LINK) $(LIB) $(MODULES)
	
clean:
	rm -f *.o $(LIB) logfile.txt 
