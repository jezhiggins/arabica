bin_PROGRAMS = pyx simple_handler writer xmlbase

LIBARABICA = $(top_builddir)/src/libarabica.la

pyx_SOURCES = pyx.cpp
pyx_LDADD =  $(LIBARABICA)

simple_handler_SOURCES = SimpleHandler.cpp SimpleHandler.h wrapper.cpp
simple_handler_LDADD = $(LIBARABICA)

writer_SOURCES = writer.cpp
writer_LDADD = $(LIBARABICA)

xmlbase_SOURCES = xmlbase.cpp
xmlbase_LDADD = $(LIBARABICA)

INCLUDES = -I$(top_srcdir)/include $(PARSER_HEADERS) $(BOOST_CPPFLAGS)
