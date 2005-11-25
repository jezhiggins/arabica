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
XPATH_HDRS = $(patsubst %.cpp,%.h,$(XPATH_SRCS))
XPATH_OBJS = $(patsubst %.cpp,%.o,$(XPATH_SRCS))

######################################
# High level rules
all : xpath_test_wide$(EXESUFFIX)

xpath_test_wide$(EXESUFFIX) : $(XPATH_OBJS) $(CPPUNIT_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(XPATH_OBJS) $(CPPUNIT_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) xpath_test_wide$(EXESUFFIX) ../../bin

######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(CPPUNIT_OBJS) \
		$(XPATH_OBJS) \
		xpath_test_wide$(EXESUFFIX) \
		 ../../bin/xpath_test_wide$(EXESUFFIX) 

# End of File
