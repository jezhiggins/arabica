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

TRANSCODE_SRCS = transcode.cpp
TRANSCODE_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(TRANSCODE_SRCS)))
TRANSCODE_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(TRANSCODE_SRCS)))

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : transcode

transcode : $(TRANSCODE_OBJS)
	$(LINK.cc) -o $@ $(TRANSCODE_OBJS)
	cp transcode ../../bin

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
	$(REMOVE) .depend *.o core transcode ../../bin/transcode



#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File



