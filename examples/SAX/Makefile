
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
PYX_SRCS = pyx.cpp
PYX_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(PYX_SRCS)))
PYX_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(PYX_SRCS)))

SIMPLE_SRCS = wrapper.cpp SimpleHandler.cpp
SIMPLE_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(SIMPLE_SRCS)))
SIMPLE_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SIMPLE_SRCS)))

WRITER_SRCS = writer.cpp
WRITER_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(WRITER_SRCS)))
WRITER_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(WRITER_SRCS)))

######################################
# High level rules
all : pyx simple_handler writer

pyx : $(PYX_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(PYX_OBJS)
	$(COPY) pyx ../../bin

simple_handler : $(SIMPLE_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(SIMPLE_OBJS)
	$(COPY) simple_handler ../../bin

writer : $(WRITER_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(WRITER_OBJS)
	$(COPY) writer ../../bin

######################
# Compile rules
####
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

######################
# Cleaning up
clean :
	$(REMOVE) *.o core pyx writer simple_handler ../../bin/pyx ../../bin/writer ../../bin/simple_handler

# End of File
