#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Utilities

REMOVE = rm -rf
LINK = ln -sf

# For GNU make:
OS_VER := $(shell uname -s | sed -e s/\[\.\ \]/_/g)
# For other make (like Sun's) you can try:
# OS_VER:sh =uname -sr | sed -e s/\[\.\ \]/_/g

# C/C++ shortcuts
CXX = c++

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

ifeq ($(OS_VER),SunOS)
CXXFLAGS = -Wall -pthreads -fpic
else
CXXFLAGS = -Wall
endif

LDFLAGS = 
CCDEPFLAGS = -E -M

# Uncomment for optimisations
CXXFLAGS += -O2
LDFLAGS  += -O2 

# Uncomment for debug version
#  CXXFLAGS += -g -D__DEBUG__


# Includes and library directories 
INCS_DIRS = -I../.. 
#INCS_DIRS = -I.. 

LIBS_DIRS = -L../../bin 

STATIC_LIBS =
DYNAMIC_LIBS = -lArabica  -lexpat

CXXFLAGS += ${INCS_DIRS}
LDFLAGS += ${LIBS_DIRS}
LDFLAGS += ${DYNAMIC_LIBS}

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

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
	$(LINK.cc) -o $@ $(PYX_OBJS)
	cp pyx ../../bin

simple_handler : $(SIMPLE_OBJS)
	$(LINK.cc) -o $@ $(SIMPLE_OBJS)
	cp simple_handler ../../bin

writer : $(WRITER_OBJS)
	$(LINK.cc) -o $@ $(WRITER_OBJS)
	cp writer ../../bin

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Compile rules

%.o : %.cpp
	$(COMPILE.cc) -o $@ $<

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Dependencies

depend : .depend

.depend ::
	$(COMPILE.cc) $(CCDEPFLAGS) ${PYX_SRCS} $(WRITER_SRCS) ${SIMPLE_SRCS} > .depend

-include .depend


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Cleaning up

clean :
	$(REMOVE) .depend *.o core pyx writer simple_handler ../../bin/pyx ../../bin/writer ../../bin/simple_handler



#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
