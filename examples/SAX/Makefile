#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Utilities

REMOVE = rm -rf
LINK = ln -sf


# C/C++ shortcuts
CPP = /usr/local/bin/gcc

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////
# Compile and link flags...
#
# -c 		Produce object code.
# -Wall		Max warning level.
# -Werror	Treat warnings as errors.
# -O2 		Turn on medium optimisations.
# -g            Add debug information.
# -D            Define symbolic constant.
# -fPIC         Generate position independent code. 
# -shared       Produce a sharable object.
#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

COMPILE_FLAGS = -Wall -c -g

LINK_FLAGS = -Wall 

# Uncomment for optimisations
#  COMPILE_FLAGS += -02
#  LINK_FLAGS    += -02

# Uncomment for debug version
#  COMPILE_FLAGS += -g -D__DEBUG__
#  LINK_FLAGS    += -g -D__DEBUG__


# Includes and library directories 
#INCS_DIRS = -I../.. -I../../include -I/usr/local/include/stlport 
INCS_DIRS = -I../.. -I../../include

#LIBS_DIRS = -L/usr/local/lib -L../../bin 
LIBS_DIRS = -L../../bin

#STATIC_LIBS = -lstlport_gcc -lSAX -lexpat  -lstdc++ 
STATIC_LIBS = -lSAX -lstdc++

PARSER_LIBS = -lexpat

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Source files

PYX_SRCS = pyx.cpp
PYX_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(PYX_SRCS)))
PYX_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(PYX_SRCS)))

SIMPLE_SRCS = wrapper.cpp SimpleHandler.cpp
SIMPLE_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(SIMPLE_SRCS)))
SIMPLE_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SIMPLE_SRCS)))

WRITER_SRCS = writer.cpp
WRITER_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(WRITER_SRCS)))
WRITER_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(WRITER_SRCS)))

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : pyx simple_handler writer

pyx : $(PYX_OBJS)
	$(CPP) $(PYX_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(PARSER_LIBS) -o pyx 
	cp pyx ../../bin

simple_handler : $(SIMPLE_OBJS)
	$(CPP) $(SIMPLE_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(PARSER_LIBS) -o simple_handler 
	cp simple_handler ../../bin

writer : $(WRITER_OBJS)
	$(CPP) $(WRITER_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(PARSER_LIBS) -o writer 
	cp writer ../../bin

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Compile rules

%.o : %.cpp
	$(CPP) $(COMPILE_FLAGS) $(INCS_DIRS) -o $@ $<


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Dependencies

depend : .depend

.depend ::
	$(CPP) $(COMPILE_FLAGS) $(INCS_DIRS) -MM $(SRCS) > .depend

-include .depend


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Cleaning up

clean :
	$(REMOVE) .depend *.o  core pyx writer simple_handler ../../bin/pyx ../../bin/writer ../../bin/simple_handler


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
