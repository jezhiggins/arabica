bin_PROGRAMS = domwriter

LIBARABICA = $(top_builddir)/src/libarabica.la

domwriter_SOURCES = DOMWriter.cpp
domwriter_LDADD = $(LIBARABICA)

INCLUDES = -I$(top_srcdir)/include $(PARSER_HEADERS) $(BOOST_CPPFLAGS)