
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
DOMTEST_TESTS = ..\DOM\dom_test_suite.hpp \
                ..\DOM\test_Attribute.h \
                ..\DOM\test_CDATA.hpp \
                ..\DOM\test_CharacterData.hpp \
                ..\DOM\test_DOMImplementation.h \
                ..\DOM\test_Document.h \
                ..\DOM\test_DocumentFragment.h \
                ..\DOM\test_DocumentType.h \
                ..\DOM\test_Element.h \
                ..\DOM\test_ProcessingInstruction.h \
                ..\DOM\test_Siblings.h \
                ..\DOM\test_Text.hpp

######################################
# High level rules
all : dom_test_wide 

dom_test_wide : $(DOMTEST_OBJS) $(CPPUNIT_OBJS) 
	$(LD) $(LDFLAGS) -o $@ $(DOMTEST_OBJS) $(CPPUNIT_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) dom_test_wide$(EXESUFFIX) ../../bin


######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNIT_OBJS) \
		$(DOMTEST_OBJS) \
		dom_test_wide$(EXESUFFIX) \
		../../bin/dom_test_wide$(EXESUFFIX) 

# End of File
