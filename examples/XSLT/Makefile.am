bin_PROGRAMS = mangle 

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ @BOOST_CPPFLAGS@
LIBARABICA = $(top_builddir)/src/libarabica.la

mangle_SOURCES = mangle.cpp 
mangle_LDADD = $(LIBARABICA)



