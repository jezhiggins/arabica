
-include ../../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../.. 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

######################################
# SOURCE FILES
TRANSCODE_SRCS = transcode.cpp
TRANSCODE_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(TRANSCODE_SRCS)))
TRANSCODE_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(TRANSCODE_SRCS)))

######################################
# High level rules
all : transcode

transcode : $(TRANSCODE_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(TRANSCODE_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) transcode$(EXESUFFIX) ../../bin


######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up

clean :
	$(REMOVE) $(TRANSCODE_OBJS) \
		transcode$(EXESUFFIX) \
		../../bin/transcode$(EXESUFFIX)

# End of File



