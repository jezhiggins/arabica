
-include ../../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../.. 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

############
CXXFLAGS += $(INCS_DIRS)
LDFLAGS += $(LIBS_DIRS)
LDFLAGS += $(STATIC_LIBS)
LDFLAGS += $(DYNAMIC_LIBS)

######################################
# SOURCE FILES
TRANSCODE_SRCS = transcode.cpp
TRANSCODE_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(TRANSCODE_SRCS)))
TRANSCODE_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(TRANSCODE_SRCS)))

######################################
# High level rules
all : transcode

transcode : $(TRANSCODE_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(TRANSCODE_OBJS)
	$(COPY) transcode ../../bin


######################
# Compile rules
####
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

######################
# Cleaning up

clean :
	$(REMOVE) $(TRANSCODE_OBJS) core transcode ../../bin/transcode

# End of File



