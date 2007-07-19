
noinst_PROGRAMS = xslt_test 

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


test_sources = scope_test.hpp 

xslt_test_SOURCES = main.cpp $(cppunit_sources) $(test_sources)
xslt_test_LDADD =  $(LIBARABICA)
xslt_test_DEPENDENCIES = $(LIBARABICA)

test: $(noinst_PROGRAMS)
	@for p in $(noinst_PROGRAMS); do \
	  echo Running $$p; \
	  ./$$p -q; \
	done

