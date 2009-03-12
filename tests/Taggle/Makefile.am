
check_PROGRAMS = taggle_test 
if WANT_TESTS
  TESTS = $(check_PROGRAMS)
endif


AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA =  $(top_builddir)/src/libarabica.la
TESTLIBS = $(LIBARABICA) ../CppUnit/libcppunit.la

test_sources = test_Taggle.hpp 

taggle_test_SOURCES = taggle_test.cpp \
                      $(test_sources) 
taggle_test_LDADD =  $(TESTLIBS)
taggle_test_DEPENDENCIES = $(TESTLIBS)


