
noinst_PROGRAMS = xpath_test xpath_test_silly 
if HAS_STD_WSTRING
  noinst_PROGRAMS += xpath_test_wide
endif

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ @BOOST_CPPFLAGS@
LIBARABICA =  $(top_builddir)/src/libarabica.la

cppunit_sources = ../CppUnit/framework/CppUnitException.h \
                   ../CppUnit/framework/estring.h \
                   ../CppUnit/framework/Guards.h \
                   ../CppUnit/framework/Test.h \
                   ../CppUnit/framework/TestCaller.h \
                   ../CppUnit/framework/TestCase.cpp \
                   ../CppUnit/framework/TestCase.h \
                   ../CppUnit/framework/TestFailure.cpp \
                   ../CppUnit/framework/TestFailure.h \
                   ../CppUnit/framework/TestResult.cpp \
                   ../CppUnit/framework/TestResult.h \
                   ../CppUnit/framework/TestSuite.cpp \
                   ../CppUnit/framework/TestSuite.h \
                   ../CppUnit/TestRunner.cpp \
                   ../CppUnit/TestRunner.hpp \
                   ../CppUnit/textui/TextTestResult.cpp \
                   ../CppUnit/textui/TextTestResult.h


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
               value_test.hpp \
               xpath_test_suite.hpp

xpath_test_SOURCES = main.cpp $(cppunit_sources) $(test_sources)
xpath_test_LDADD =  $(LIBARABICA)
xpath_test_DEPENDENCIES = $(LIBARABICA)

xpath_test_silly_SOURCES = main_silly.cpp $(cppunit_sources) $(test_sources) ../silly_string/silly_string.cpp
xpath_test_silly_LDADD =  $(LIBARABICA)
xpath_test_silly_DEPENDENCIES = $(LIBARABICA)

xpath_test_wide_SOURCES = main_wide.cpp $(cppunit_sources) $(test_sources) 
xpath_test_wide_LDADD =  $(LIBARABICA)
xpath_test_wide_DEPENDENCIES = $(LIBARABICA)



test: $(noinst_PROGRAMS)
	@for p in $(noinst_PROGRAMS); do \
	  echo Running $$p; \
	  ./$$p -q; \
	done
