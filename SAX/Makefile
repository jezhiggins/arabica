####################################
# Arabica Makefile
#
# I wrote this for GNU Make + GNU tools on Linux.
# You may have to jiggle it for your own environment.
# Platforms specific build files gratefully received 
# at jez@jezuk.co.uk  Thanks :)
#
# $Id$
####################################

-include ../Makefile.header

######################################
# ADDITIONAL BUILD FLAGS
CXXFLAGS += -I..
LDFLAGS += $(LINK_SHARED)

INC_DIRS +=
LIBS_DIRS +=

STATIC_LIBS +=
DYNAMIC_LIBS +=

######################################
# SOURCE FILES
SRCS =  saxlib.cpp \
	helpers/InputSourceResolver.cpp \
	../Utils/rot13codecvt.cpp \
	../Utils/utf8ucs2codecvt.cpp \
	../Utils/impl/ucs2_utf8.cpp \
	../Utils/utf16beucs2codecvt.cpp \
	../Utils/utf16leucs2codecvt.cpp \
	../Utils/impl/ucs2_utf16.cpp \
	../Utils/iso88591utf8codecvt.cpp \
	../Utils/utf8iso88591codecvt.cpp \
	../Utils/impl/iso88591_utf8.cpp \
	../Utils/utf16utf8codecvt.cpp \
	../Utils/base64codecvt.cpp \
	../Utils/impl/codecvt_specialisations.cpp \
	../XML/XMLCharacterClasses.cpp

HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(SRCS)))
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

##########################
# High level rules
all : libArabica($LIBSUFFIX)

libArabica($LIBSUFFIX) : $(OBJS)
	$(LD) $(LDFLAGS) -o libArabica$(LIBSUFFIX) $(OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) libArabica$(LIBSUFFIX) ../bin

######################
# Compile rules
####
# the .S files depends on symbols defined in this Makefile, hence
# this slightly wacky rule
saxlib.cpp : ParserConfig.h ArabicaConfig.h
	$(CPP) $(PARSER_CONFIG) -o saxlib.cpp saxlib.S 

ParserConfig.h : Makefile ../Makefile.header
	$(CPP) $(PARSER_CONFIG) -o ParserConfig.h ParserConfig.S

ArabicaConfig.h : Makefile ../Makefile.header
	$(CPP) $(PARSER_CONFIG) -o ArabicaConfig.h ArabicaConfig.S

%.cpp : ArabicaConfig.h ParserConfig.h

Makefile :

-include ../Makefile.rules

#############################################
# Cleaning up
clean :
	$(REMOVE) *.o helpers/*.o wrappers/*.o ../Utils/*.o ../Utils/impl/*.o ../XML/*.o libArabica*  ../bin/libArabica* saxlib.cpp ParserConfig.h ArabicaConfig.h

# End of File






