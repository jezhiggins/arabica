
-include ../../Makefile.header
-include ../../Makefile.common

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../.. 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

######################################
# SOURCE FILES
DOMTEST_SRCS = main.cpp
DOMTEST_OBJS = $(patsubst %.cpp,%.o,$(DOMTEST_SRCS))
DOMTEST_TESTS = dom_test_suite.hpp \
                test_Attribute.h \
                test_CDATA.hpp \
                test_CharacterData.hpp \
                test_DOMImplementation.h \
                test_Document.h \
                test_DocumentFragment.h \
                test_DocumentType.h \
                test_Element.h \
                test_ProcessingInstruction.h \
                test_Siblings.h \
                test_Text.hpp

######################################
# High level rules
all : dom_test 

dom_test : $(DOMTEST_OBJS) $(CPPUNIT_OBJS) 
	$(LD) $(LDFLAGS) -o $@ $(DOMTEST_OBJS) $(CPPUNIT_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) dom_test$(EXESUFFIX) ../../bin


######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNIT_OBJS) \
		$(DOMTEST_OBJS) \
		dom_test$(EXESUFFIX) \
		../../bin/dom_test$(EXESUFFIX) 

# End of File
