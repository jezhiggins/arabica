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

LDFLAGS = 
CCDEPFLAGS = -E -M

# Uncomment for optimisations
CXXFLAGS += -O2
LDFLAGS  += -O2 -L../../bin -lSAX -lArabicaUtils 

# Uncomment for debug version
CXXFLAGS += -g -D__DEBUG__


# Includes and library directories 
INCS_DIRS = -I../..
#INCS_DIRS = -I.. 

LIBS_DIRS = 

STATIC_LIBS =
DYNAMIC_LIBS = -L../../bin -lSAX -lexpat 

CXXFLAGS += ${INCS_DIRS}
LDFLAGS += ${DYNAMIC_LIBS}

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Source files
SAXDOM_SRCS = main.cpp test_Attribute.cpp test_Document.cpp test_DocumentFragment.cpp test_DocumentType.cpp test_DOMImplementation.cpp test_Element.cpp test_ProcessingInstruction.cpp test_Siblings.cpp test_SAX.cpp
SAXDOM_HDRS = $(patsubst %.cpp,%.h,$(SAXDOM_SRCS))
SAXDOM_OBJS = $(patsubst %.cpp,%.o,$(SAXDOM_SRCS))

CPPUNITFW_FILES = TestCase.cpp TestFailure.cpp TestResult.cpp TestSuite.cpp
CPPUNITFW_SRCS = $(patsubst Test%,CppUnit/framework/Test%,$(CPPUNITFW_FILES))
CPPUNITFW_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITFW_SRCS))

CPPUNITUI_FILES = TextTestResult.cpp
CPPUNITUI_SRCS = $(patsubst Text%,CppUnit/textui/Text%,$(CPPUNITUI_FILES))
CPPUNITUI_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITUI_SRCS))

#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : sax2dom_test


sax2dom_test : $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS)
	$(LINK.cc) -o $@ $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS)
	cp sax2dom_test ../../bin

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
	$(COMPILE.cc) $(CCDEPFLAGS) $(SAXDOM_SRCS) $(CPPUNITFW_SRCS) $(CPPUNITUI_SRCS) > .depend

-include .depend


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Cleaning up

clean :
	$(REMOVE) .depend $(CPPUNITUI_OBJS) $(CPPUNITFW_OBJS) $(SAXDOM_OBJS) core sax2dom_test ../../bin/sax2dom_test


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
