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

LDFLAGS = -shared -Wl,"-hlibArabica.so.1"
CCDEPFLAGS = -E -M

# Uncomment for optimisations
CXXFLAGS += -O2
LDFLAGS  += -O2

# edit for your parser choice - may include more than one
PARSER_CONFIG = -DUSE_EXPAT -DARABICA_NO_WCHAR_T
#PARSER_CONFIG = -DUSE_EXPAT -DUSE_LIBXML2 -DUSE_XERCES -DUSE_GARDEN

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

SRCS =  saxlib.cpp \
	helpers/InputSourceResolver.cpp \
	../Utils/base64codecvt.cpp \
	../Utils/iso88591utf8codecvt.cpp \
	../Utils/rot13codecvt.cpp \
	../Utils/utf16beucs2codecvt.cpp \
	../Utils/utf16leucs2codecvt.cpp \
	../Utils/utf16utf8codecvt.cpp \
	../Utils/utf8iso88591codecvt.cpp \
	../Utils/utf8ucs2codecvt.cpp \
	../Utils/impl/iso88591_utf8.cpp \
	../Utils/impl/ucs2_utf16.cpp \
	../Utils/impl/ucs2_utf8.cpp \
	../XML/XMLCharacterClasses.cpp


HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(SRCS)))
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : libArabica.so.1 libArabica.a 

libArabica.so.1 : $(OBJS)
	$(LINK.cc) -o $@ $(OBJS)
	cp -f libArabica.so.1 ../bin
	(cd ../bin; rm -f libArabica.so; ln -s libArabica.so.1 libArabica.so)

#	$(LINK) $@ libArabica.so

libArabica.a : $(OBJS)
	ar r $@ $(OBJS)
	cp -f libArabica.a ../bin

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Compile rules
saxlib.cpp : ParserConfig.S saxlib.S ArabicaConfig.S
	$(PREPROCESS.S) $(PARSER_CONFIG) -o ArabicaConfig.h ArabicaConfig.S
	$(PREPROCESS.S) $(PARSER_CONFIG) -o ParserConfig.h ParserConfig.S
	$(PREPROCESS.S) $(PARSER_CONFIG) -o saxlib.cpp saxlib.S 


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
	$(REMOVE) .depend *.o helpers/*.o wrappers/*.o ../Utils/*.o ../Utils/impl/*.o ../XML/*.o libArabica*  *~ helpers/*~ core ../bin/libArabica* saxlib.cpp ParserConfig.h ArabicaConfig.h



#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
