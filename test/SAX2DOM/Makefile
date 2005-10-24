
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

######################################
# High level rules
all : sax2dom_test 

sax2dom_test : $(SAXDOM_OBJS) $(CPPUNIT_OBJS) 
	$(LD) $(LDFLAGS) -o $@ $(SAXDOM_OBJS) $(CPPUNIT_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) sax2dom_test$(EXESUFFIX) ../../bin


######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNIT_OBJS) \
		$(SAXDOM_OBJS) \
		sax2dom_test$(EXESUFFIX) \
		 ../../bin/sax2dom_test$(EXESUFFIX) 

# End of File
