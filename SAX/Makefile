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
	../Utils/ucs2utf8codecvt.cpp \
	../Utils/base64codecvt.cpp \
	../XML/XMLCharacterClasses.cpp 

HDRS = $(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(SRCS)))
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

##########################
# High level rules
all : libArabica$(LIBSUFFIX)

libArabica$(LIBSUFFIX) : $(OBJS)
	$(LD) $(LDFLAGS) -o libArabica$(LIBSUFFIX) $(OBJS) $(LIBS_DIRS) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(COPY) libArabica$(LIBSUFFIX) ../bin

######################
# Compile rules
####
# the .S files depends on symbols defined in this Makefile, hence
# this slightly wacky rule
saxlib.cpp : ../include/SAX/ParserConfig.h ../include/SAX/ArabicaConfig.h saxlib.S
	$(CPP) $(PARSER_CONFIG) -o saxlib.cpp saxlib.S 

../include/SAX/ParserConfig.h : Makefile ../Makefile.header ParserConfig.S
	$(CPP) $(PARSER_CONFIG) -o ../include/SAX/ParserConfig.h ParserConfig.S

../include/SAX/ArabicaConfig.h : Makefile ../Makefile.header ArabicaConfig.S
	$(CPP) $(PARSER_CONFIG) -o ../include/SAX/ArabicaConfig.h ArabicaConfig.S

%.cpp : ../include/SAX/ArabicaConfig.h ../include/SAX/ParserConfig.h

Makefile :

-include ../Makefile.rules

#############################################
# Cleaning up
clean :
	$(REMOVE) wrappers/*.o $(OBJS) libArabica*  ../bin/libArabica* saxlib.cpp ../include/SAX/ParserConfig.h ../include/SAX/ArabicaConfig.h

# End of File






