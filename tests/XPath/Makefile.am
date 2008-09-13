
check_PROGRAMS = xpath_test xpath_test_silly 
if HAS_STD_WSTRING
  check_PROGRAMS += xpath_test_wide
endif
if WANT_TESTS
  TESTS = $(check_PROGRAMS)
endif


AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ @BOOST_CPPFLAGS@
LIBARABICA =  $(top_builddir)/src/libarabica.la
LIBSILLY = ../CppUnit/libsillystring.la
TESTLIBS = $(LIBARABICA) ../CppUnit/libcppunit.la

test_sources = arithmetic_test.hpp \
               attr_value_test.hpp \
               axis_enumerator_test.hpp \
               execute_test.hpp \
               expression_test.hpp \
               logical_test.hpp \
               match_test.hpp \
               node_test_test.hpp \
               parse_test.hpp \
               relational_test.hpp \
               step_test.hpp \
               text_node_test.hpp \
               value_test.hpp \
               xpath_test_suite.hpp

xpath_test_SOURCES = main.cpp \
                     $(test_sources)
xpath_test_LDADD = $(TESTLIBS)
xpath_test_DEPENDENCIES = $(TESTLIBS)

xpath_test_silly_SOURCES = main_silly.cpp \
                           $(test_sources) 
xpath_test_silly_LDADD = $(TESTLIBS) $(LIBSILLY)
xpath_test_silly_DEPENDENCIES = $(TESTLIBS) $(LIBSILLY)

xpath_test_wide_SOURCES = main_wide.cpp \
                          $(test_sources) 
xpath_test_wide_LDADD = $(TESTLIBS)
xpath_test_wide_DEPENDENCIES = $(TESTLIBS)

