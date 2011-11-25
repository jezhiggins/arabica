
check_PROGRAMS = xslt_test 
if WANT_TESTS
  TESTS = $(check_PROGRAMS)
endif

ELEPHANT_INCLUDE = @ELEPHANT_INCLUDES@
LIBELEPHANT = @ELEPHANT_LIBS@

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ @BOOST_CPPFLAGS@ $(ELEPHANT_INCLUDE)
LIBARABICA =  $(top_builddir)/src/libarabica.la
LIBSILLY = ../CppUnit/libsillystring.la
TESTLIBS = $(LIBARABICA) ../CppUnit/libcppunit.la  
SYSLIBS = @PARSER_LIBS@

test_sources = scope_test.hpp \
               xslt_test.hpp \
               xslt_test.cpp


xslt_test_SOURCES = main.cpp \
                    $(test_sources)
xslt_test_LDADD =  $(TESTLIBS) $(LIBELEPHANT) $(SYSLIBS)
xslt_test_DEPENDENCIES = $(TESTLIBS)

