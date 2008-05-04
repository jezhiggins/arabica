noinst_PROGRAMS = domwriter dom2pyx

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA = $(top_builddir)/src/libarabica.la

domwriter_SOURCES = DOMWriter.cpp
domwriter_LDADD = $(LIBARABICA)

dom2pyx_SOURCES = dom2pyx.cpp
dom2pyx_LDADD = $(LIBARABICA)

