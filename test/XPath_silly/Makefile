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
XPATH_TESTS = ../XPath/arithmetic_test.hpp \
              ../XPath/axis_enumerator_test.hpp \
              ../XPath/execute_test.hpp \
              ../XPath/logical_test.hpp \
              ../XPath/node_test_test.hpp \
              ../XPath/parse_test.hpp \
              ../XPath/relational_test.hpp \
              ../XPath/step_test.hpp \
              ../XPath/value_test.hpp \
              ../XPath/xpath_test_suite.hpp
XPATH_OBJS = $(patsubst %.cpp,%.o,$(XPATH_SRCS))

######################################
# High level rules
all : xpath_test_ss

xpath_test_ss : $(XPATH_OBJS) $(CPPUNIT_OBJS) $(XPATH_TESTS)
	$(LD) $(LDFLAGS) -o $@ $(XPATH_OBJS) $(CPPUNIT_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) xpath_test_ss$(EXESUFFIX) ../../bin

######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNIT_OBJS) \
		$(XPATH_OBJS) \
		xpath_test_ss$(EXESUFFIX) \
		 ../../bin/xpath_test_ss$(EXESUFFIX) 


