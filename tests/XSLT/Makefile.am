
check_PROGRAMS = xslt_test 
TESTS = $(check_PROGRAMS)

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ @BOOST_CPPFLAGS@
LIBARABICA =  $(top_builddir)/src/libarabica.la
LIBSILLY = ../CppUnit/libsillystring.la
TESTLIBS = $(LIBARABICA) ../CppUnit/libcppunit.la

test_sources = scope_test.hpp \
               xslt_test.hpp

xslt_test_SOURCES = main.cpp \
                    $(test_sources)
xslt_test_LDADD =  $(TESTLIBS)
xslt_test_DEPENDENCIES = $(TESTLIBS)

