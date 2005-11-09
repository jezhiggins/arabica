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
XPATH_SRCS = main.cpp 
XPATH_TESTS = arithmetic_test.hpp axis_enumerator_test.hpp execute_test.hpp logical_test.hpp node_test_test.hpp parse_test.hpp relational_test.hpp step_test.hpp value_test.hpp
XPATH_OBJS = $(patsubst %.cpp,%.o,$(XPATH_SRCS))

######################################
# High level rules
all : xpath_test 

xpath_test : $(XPATH_OBJS) $(CPPUNIT_OBJS) $(XPATH_TESTS)
	$(LD) $(LDFLAGS) -o $@ $(XPATH_OBJS) $(CPPUNIT_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) xpath_test$(EXESUFFIX) ../../bin

######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNIT_OBJS) \
		$(XPATH_OBJS) \
		xpath_test$(EXESUFFIX) \
		 ../../bin/xpath_test$(EXESUFFIX) 


