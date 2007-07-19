noinst_PROGRAMS = xgrep 

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ @BOOST_CPPFLAGS@
LIBARABICA = $(top_builddir)/src/libarabica.la

xgrep_SOURCES = xgrep.cpp
xgrep_LDADD = $(LIBARABICA)


