bin_PROGRAMS = xgrep 

LIBARABICA = $(top_builddir)/src/libarabica.la

xgrep_SOURCES = xgrep.cpp
xgrep_LDADD = $(LIBARABICA)

INCLUDES = -I$(top_srcdir)/include $(PARSER_HEADERS) $(BOOST_CPPFLAGS)

jez:
	echo @top_builddir@

