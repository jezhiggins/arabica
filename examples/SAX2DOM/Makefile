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
STATIC_LIBS = -lSAX -lexpat -lstdc++



#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Source files
SAXDOM_SRCS = main.cpp test_Attribute.cpp test_Document.cpp test_DocumentFragment.cpp test_DocumentType.cpp test_DOMImplementation.cpp test_Element.cpp test_ProcessingInstruction.cpp test_Siblings.cpp
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

all : SAX2DOM

SAX2DOM : $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS)
	$(CPP) $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) -o sax2dom_test 
	cp sax2dom_test ../../bin

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
	$(REMOVE) .depend core sax2dom_test ../../bin/sax2dom_test $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS)


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
