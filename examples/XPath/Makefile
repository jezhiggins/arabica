
-include ../../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../../include 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

######################################
# SOURCE FILES
XGREP_SRCS = xgrep.cpp
XGREP_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(XGREP_SRCS)))
XGREP_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(XGREP_SRCS)))

######################################
# High level rules
all : xgrep$(EXESUFFIX)

xgrep$(EXESUFFIX) : $(XGREP_OBJS)
	$(LD) $(LDFLAGS)  -o $@ $(XGREP_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) xgrep$(EXESUFFIX) ../../bin

######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(XGREP_OBJS) \
		xgrep$(EXESUFFIX) \
		 ../../bin/xgrep$(EXESUFFIX)

# End of File
