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

LDFLAGS = -shared -Wl,"-hlibSAX.so.1"
CCDEPFLAGS = -E -M

# Uncomment for optimisations
CXXFLAGS += -O2
LDFLAGS  += -O2

# Uncomment for debug version
#  CXXFLAGS += -g -D__DEBUG__


# Includes and library directories 
INCS_DIRS = -I.. -I/usr/local/include/stlport -I/opt/gnome2/include/libxml2
#INCS_DIRS = -I.. 

LIBS_DIRS = 

STATIC_LIBS =
DYNAMIC_LIBS = -lstlport_gcc -L/opt/gnome2/lib -lxml2

CXXFLAGS += ${INCS_DIRS}
LDFLAGS += ${DYNAMIC_LIBS}

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

SRCS =  wrappers/saxexpat.cpp \
	wrappers/saxlibxml2.cpp \
	helpers/InputSourceResolver.cpp \
	../Utils/utf16utf8_codecvt.cpp 

HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(SRCS)))
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : libSAX.so.1 libSAX.a 

libSAX.so.1 : $(OBJS)
	$(LINK.cc) -o $@ $(OBJS)
	cp -f libSAX.so.1 ../bin
	(cd ../bin; rm -f libSAX.so; ln -s libSAX.so.1 libSAX.so)

#	$(LINK) $@ libSAX.so

libSAX.a : $(OBJS)
	ar r $@ $(OBJS)
	cp -f libSAX.a ../bin

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
	$(REMOVE) .depend *.o helpers/*.o wrappers/*.o ../Utils/*.o libSAX*  *~ helpers/*~ core ../bin/libSAX*



#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
