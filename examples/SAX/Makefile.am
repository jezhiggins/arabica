noinst_PROGRAMS = pyx simple_handler writer xmlbase

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA = $(top_builddir)/src/libarabica.la

pyx_SOURCES = pyx.cpp
pyx_LDADD =  $(LIBARABICA)

simple_handler_SOURCES = SimpleHandler.cpp SimpleHandler.hpp wrapper.cpp
simple_handler_LDADD = $(LIBARABICA)

writer_SOURCES = writer.cpp
writer_LDADD = $(LIBARABICA)

xmlbase_SOURCES = xmlbase.cpp
xmlbase_LDADD = $(LIBARABICA)

