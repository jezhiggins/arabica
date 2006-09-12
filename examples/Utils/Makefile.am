bin_PROGRAMS = transcode

LIBARABICA = $(top_builddir)/src/libarabica.la

transcode_SOURCES = transcode.cpp
transcode_LDADD = $(LIBARABICA)

INCLUDES = -I$(top_srcdir)/include $(PARSER_HEADERS) $(BOOST_CPPFLAGS)