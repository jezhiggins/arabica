
-include ../../Makefile.header
-include ../../Makefile.common

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../../include
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

######################################
# SOURCE FILES
SAXDOM_SRCS = main.cpp ../silly_string/silly_string.cpp
SAXDOM_HDRS = $(patsubst %.cpp,%.h,$(SAXDOM_SRCS))
SAXDOM_OBJS = $(patsubst %.cpp,%.o,$(SAXDOM_SRCS))

######################################
# High level rules
all : sax2dom_test$(EXESUFFIX)

sax2dom_test$(EXESUFFIX) : $(SAXDOM_OBJS) $(CPPUNIT_OBJS) 
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
