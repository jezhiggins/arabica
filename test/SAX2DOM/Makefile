
-include ../../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../.. 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

######################################
# SOURCE FILES
SAXDOM_SRCS = main.cpp test_Attribute.cpp test_Document.cpp test_DocumentFragment.cpp test_DocumentType.cpp test_DOMImplementation.cpp test_Element.cpp test_ProcessingInstruction.cpp test_Siblings.cpp test_SAX.cpp test_CDATA.cpp test_CharacterData.cpp test_Text.cpp
SAXDOM_HDRS = $(patsubst %.cpp,%.h,$(SAXDOM_SRCS))
SAXDOM_OBJS = $(patsubst %.cpp,%.o,$(SAXDOM_SRCS))

CPPUNITFW_FILES = TestCase.cpp TestFailure.cpp TestResult.cpp TestSuite.cpp
CPPUNITFW_SRCS = $(patsubst Test%,../CppUnit/framework/Test%,$(CPPUNITFW_FILES))
CPPUNITFW_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITFW_SRCS))

CPPUNITUI_FILES = TextTestResult.cpp
CPPUNITUI_SRCS = $(patsubst Text%,../CppUnit/textui/Text%,$(CPPUNITUI_FILES))
CPPUNITUI_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITUI_SRCS))

######################################
# High level rules
all : sax2dom_test 

sax2dom_test : $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(SAXDOM_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) sax2dom_test$(EXESUFFIX) ../../bin


######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNITUI_OBJS) \
		$(CPPUNITFW_OBJS) \
		$(SAXDOM_OBJS) \
		sax2dom_test$(EXESUFFIX) \
		 ../../bin/sax2dom_test$(EXESUFFIX) 

# End of File
