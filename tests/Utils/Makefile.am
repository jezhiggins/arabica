
check_PROGRAMS = utils_test utils_test_silly
if HAS_STD_WSTRING
  check_PROGRAMS += utils_test_wide
endif
if WANT_TESTS
  TESTS = $(check_PROGRAMS)
endif

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA =  $(top_builddir)/src/libarabica.la
LIBSILLY = ../CppUnit/libsillystring.la
TESTLIBS = $(LIBARABICA) ../CppUnit/libcppunit.la

test_sources = util_test_suite.hpp \
               test_normalize_whitespace.hpp \
               test_xml_strings.hpp \
               test_base64.hpp \
               test_uri.hpp \
               test_qname.hpp

utils_test_SOURCES = utils_test.cpp \
                     $(test_sources)
utils_test_LDADD =  $(TESTLIBS)
utils_test_DEPENDENCIES = $(TESTLIBS)

utils_test_silly_SOURCES = utils_test_silly.cpp \
                           $(test_sources) 
utils_test_silly_LDADD =  $(TESTLIBS) $(LIBSILLY)
utils_test_silly_DEPENDENCIES = $(TESTLIBS) $(LIBSILLY)

utils_test_wide_SOURCES = utils_test_wide.cpp \
                          $(test_sources) 
utils_test_wide_LDADD =  $(TESTLIBS)
utils_test_wide_DEPENDENCIES = $(TESTLIBS)

