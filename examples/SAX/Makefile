
-include ../../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../.. 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

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

pyx$ : $(PYX_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(PYX_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) pyx$(EXESUFFIX) ../../bin

simple_handler : $(SIMPLE_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(SIMPLE_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) simple_handler$(EXESUFFIX) ../../bin

writer : $(WRITER_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(WRITER_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) writer$(EXESUFFIX) ../../bin

######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) *.o \
		core \
		pyx$(EXESUFFIX) \
		../../bin/pyx$(EXESUFFIX) \
		writer$(EXESUFFIX) \
		../../bin/writer$(EXESUFFIX) \
		simple_handler$(EXESUFFIX) \
		../../bin/simple_handler$(EXESUFFIX)

# End of File
