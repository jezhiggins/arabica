
-include ../../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../.. 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

######################################
# SOURCE FILES
DOMTEST_SRCS = main.cpp
DOMTEST_HDRS = $(patsubst %.cpp,%.h,$(DOMTEST_SRCS))
DOMTEST_OBJS = $(patsubst %.cpp,%.o,$(DOMTEST_SRCS))

######################################
# High level rules
all : sax2dom_test 

dom_test : $(DOMTEST_OBJS) $(CPPUNIT_OBJS) 
	$(LD) $(LDFLAGS) -o $@ $(DOMTEST_OBJS) $(CPPUNIT_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) sax2dom_test$(EXESUFFIX) ../../bin


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
