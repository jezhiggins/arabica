
-include ../../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../.. 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

############
CXXFLAGS += $(INCS_DIRS)
LDFLAGS += $(LIBS_DIRS)
LDFLAGS += $(STATIC_LIBS)
LDFLAGS += $(DYNAMIC_LIBS)

######################################
# SOURCE FILES
SAXDOM_SRCS = main.cpp test_Attribute.cpp test_Document.cpp test_DocumentFragment.cpp test_DocumentType.cpp test_DOMImplementation.cpp test_Element.cpp test_ProcessingInstruction.cpp test_Siblings.cpp test_SAX.cpp
SAXDOM_HDRS = $(patsubst %.cpp,%.h,$(SAXDOM_SRCS))
SAXDOM_OBJS = $(patsubst %.cpp,%.o,$(SAXDOM_SRCS))

CPPUNITFW_FILES = TestCase.cpp TestFailure.cpp TestResult.cpp TestSuite.cpp
CPPUNITFW_SRCS = $(patsubst Test%,CppUnit/framework/Test%,$(CPPUNITFW_FILES))
CPPUNITFW_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITFW_SRCS))

CPPUNITUI_FILES = TextTestResult.cpp
CPPUNITUI_SRCS = $(patsubst Text%,CppUnit/textui/Text%,$(CPPUNITUI_FILES))
CPPUNITUI_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITUI_SRCS))

DOMWRITER_SRCS = DOMWriter.cpp
DOMWRITER_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(DOMWRITER_SRCS)))
DOMWRITER_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(DOMWRITER_SRCS)))

######################################
# High level rules
all : sax2dom_test domwriter

sax2dom_test : $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS)
	$(COPY) sax2dom_test ../../bin

domwriter : $(DOMWRITER_OBJS)
	$(LD) $(LDFLAGS)  -o $@ $(DOMWRITER_OBJS)
	$(COPY) domwriter ../../bin

######################
# Compile rules
####
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNITUI_OBJS) $(CPPUNITFW_OBJS) $(SAXDOM_OBJS) $(DOMWRITER_OBJS) core sax2dom_test domwriter ../../bin/sax2dom_test ../../bin/domwriter

# End of File
