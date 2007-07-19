noinst_PROGRAMS = domwriter

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA = $(top_builddir)/src/libarabica.la

domwriter_SOURCES = DOMWriter.cpp
domwriter_LDADD = $(LIBARABICA)

