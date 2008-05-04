noinst_PROGRAMS = transcode

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA = $(top_builddir)/src/libarabica.la

transcode_SOURCES = transcode.cpp
transcode_LDADD = $(LIBARABICA)

