noinst_PROGRAMS = taggle

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA = $(top_builddir)/src/libarabica.la

taggle_SOURCES = taggle.cpp
taggle_LDADD =  $(LIBARABICA)
