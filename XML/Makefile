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
CXXFLAGS = -Wall -pthread -fpic
endif

LDFLAGS = -shared -Wl,"-hlibArabicaUtils.so.1"
CCDEPFLAGS = -E -M

# Uncomment for optimisations
CXXFLAGS += -O2
LDFLAGS  += -O2

# Uncomment for debug version
#  CXXFLAGS += -g -D__DEBUG__


# Includes and library directories 
INCS_DIRS = -I.. 
#INCS_DIRS = -I.. 

LIBS_DIRS = 

STATIC_LIBS =
DYNAMIC_LIBS = -lstdc++

CXXFLAGS += ${INCS_DIRS}
LDFLAGS += ${DYNAMIC_LIBS}

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

SRCS =  XMLCharacterClasses.cpp

HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(SRCS)))
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : libArabicaXML.so.1 libArabicaXML.a

libArabicaXML.so.1 : $(OBJS)
	$(LINK.cc) -o $@ $(OBJS)
	cp -f libArabicaXML.so.1 ../bin
	(cd ../bin; ln -fs libArabicaXML.so.1 libArabicaXML.so)

libArabicaXML.a : $(OBJS)
	ar r $@ $(OBJS)
	cp -f libArabicaXML.a ../bin

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
	$(COMPILE.cc) $(CCDEPFLAGS) $(SRCS) > .depend

-include .depend


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Cleaning up

clean :
	$(REMOVE) .depend *.o lib*  *~  core ../bin/libArabicaXML*



#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
