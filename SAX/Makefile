#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Utilities

REMOVE = rm -rf
LINK = ln -sf


# C/C++ shortcuts
CPP = /usr/local/bin/gcc


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////
# Compile and link flags...
#
# -c 		Produce object code.
# -Wall		Max warning level.
# -Werror	Treat warnings as errors.
# -O2 		Turn on medium optimisations.
# -g            Add debug information.
# -D            Define symbolic constant.
# -fPIC         Generate position independent code. 
# -shared       Produce a sharable object.
#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

COMPILE_FLAGS = -Wall -c -shared

LINK_FLAGS = -Wall -Werror -shared -Wl,-soname,libSAX.so.1

# Uncomment for optimisations
#  COMPILE_FLAGS += -02
#  LINK_FLAGS    += -02

# Uncomment for debug version
#  COMPILE_FLAGS += -g -D__DEBUG__
#  LINK_FLAGS    += -g -D__DEBUG__


# Includes and library directories 
#INCS_DIRS = -I.. -I/usr/local/include/stlport
INCS_DIRS = -I.. 

LIBS_DIRS = 

STATIC_LIBS =
DYNAMIC_LIBS = 


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Source files

SRCS = wrappers/saxexpat.cpp helpers/InputSourceResolver.cpp ../Utils/utf16utf8_codecvt.cpp 
# substitute wrappers/saxlibxml2.cpp if appropriate, or omit completely 
# if using saxxerces

HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(SRCS)))
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# High level rules

all : libSAX.a 

libSAX.so : $(OBJS)
	$(CPP) $(LIB_DIRS) $(LINK_FLAGS) -o $@ $(OBJS)
	$(LINK) $@ $@.1

libSAX.a : $(OBJS)
	ar r $@ $(OBJS)
	cp libSAX.a ../bin


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Compile rules

%.o : %.cpp
	$(CPP) $(COMPILE_FLAGS) $(INCS_DIRS) -o $@ $<


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Dependencies

depend : .depend

.depend ::
	$(CPP) $(COMPILE_FLAGS) $(INCS_DIRS) -MM $(SRCS) > .depend

-include .depend


#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# Cleaning up

clean :
	$(REMOVE) .depend *.o helpers/*.o wrappers/*.o ../Utils/*.o libSAX*  *~ helpers/*~ core ../bin/libSAX*



#/////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////

# End of File
