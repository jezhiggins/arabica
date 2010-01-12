check_PROGRAMS = filter_test filter_test_silly
if HAS_STD_WSTRING
  check_PROGRAMS += filter_test_wide
endif
if WANT_TESTS
  TESTS = $(check_PROGRAMS)
endif


AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA =  $(top_builddir)/src/libarabica.la
LIBSILLY = ../CppUnit/libsillystring.la
TESTLIBS = $(LIBARABICA) ../CppUnit/libcppunit.la

test_sources = test_WhitespaceStripper.hpp 

filter_test_SOURCES = filter_test.cpp \
                      $(test_sources) 
filter_test_LDADD =  $(TESTLIBS)
filter_test_DEPENDENCIES = $(TESTLIBS)

filter_test_silly_SOURCES = filter_test_silly.cpp \
                            $(test_sources) 
filter_test_silly_LDADD =  $(TESTLIBS) $(LIBSILLY)
filter_test_silly_DEPENDENCIES = $(TESTLIBS) $(LIBSILLY)

filter_test_wide_SOURCES = filter_test_wide.cpp \
                           $(test_sources) 
filter_test_wide_LDADD = $(TESTLIBS)
filter_test_wide_DEPENDENCIES = $(TESTLIBS)

