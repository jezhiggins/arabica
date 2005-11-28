
-include ../../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
INCS_DIRS += -I../.. 
LIBS_DIRS += -L../../bin 

STATIC_LIBS +=
DYNAMIC_LIBS += -lArabica

######################################
# SOURCE FILES
DOMWRITER_SRCS = DOMWriter.cpp
DOMWRITER_HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(DOMWRITER_SRCS)))
DOMWRITER_OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(DOMWRITER_SRCS)))

######################################
# High level rules
all : domwriter$(EXESUFFIX)

domwriter$(EXESUFFIX) : $(DOMWRITER_OBJS)
	$(LD) $(LDFLAGS)  -o $@ $(DOMWRITER_OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) domwriter$(EXESUFFIX) ../../bin

######################
# Compile rules
####
-include ../../Makefile.rules

######################
# Cleaning up
clean :
	$(REMOVE) $(DOMWRITER_OBJS) \
		domwriter$(EXESUFFIX) \
		 ../../bin/domwriter$(EXESUFFIX)

# End of File
