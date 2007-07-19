bin_PROGRAMS = mangle 

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ @BOOST_CPPFLAGS@
LIBARABICA = $(top_builddir)/src/libarabica.la

mangle_SOURCES = mangle.cpp \
                 scope_test.hpp \
                 xslt_test.hpp
mangle_LDADD = $(LIBARABICA)



