-include ../../Makefile.header

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

CPPUNIT_DIR = ../CppUnit

CPPUNITFW_FILES = TestCase.cpp TestFailure.cpp TestResult.cpp TestSuite.cpp
CPPUNITFW_SRCS = $(patsubst Test%,$(CPPUNIT_DIR)/framework/Test%,$(CPPUNITFW_FILES))
CPPUNITFW_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITFW_SRCS))

CPPUNITUI_FILES = TextTestResult.cpp
CPPUNITUI_SRCS = $(patsubst Text%,$(CPPUNIT_DIR)/textui/Text%,$(CPPUNITUI_FILES))
CPPUNITUI_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITUI_SRCS))

CPPUNITRUNNER_FILES = TestRunner.cpp
CPPUNITRUNNER_SRCS = $(patsubst Test%,$(CPPUNIT_DIR)/Test%,$(CPPUNITRUNNER_FILES))
CPPUNITRUNNER_OBJS = $(patsubst %.cpp,%.o,$(CPPUNITRUNNER_SRCS))

######################################
# High level rules
all : xpath_test 

xpath_test : $(XPATH_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS) $(CPPUNITRUNNER_OBJS) $(XPATH_TESTS)
	$(LD) $(LDFLAGS) -o $@ $(XPATH_OBJS) $(CPPUNITFW_OBJS) $(CPPUNITUI_OBJS) $(CPPUNITRUNNER_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) xpath_test$(EXESUFFIX) ../../bin

######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNITUI_OBJS) \
		$(CPPUNITFW_OBJS) \
		$(CPPUNITRUNNER_OBJS) \
		$(XPATH_OBJS) \
		xpath_test$(EXESUFFIX) \
		 ../../bin/xpath_test$(EXESUFFIX) 


