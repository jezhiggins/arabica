
noinst_PROGRAMS = filter_test filter_test_silly
TESTS = filter_test filter_test_silly
if HAS_STD_WSTRING
  noinst_PROGRAMS += filter_test_wide
  TESTS +=filter_test_wide
endif

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
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

silly_string_sources = ../silly_string/silly_string.cpp \
                       ../silly_string/silly_string.hpp

test_sources = test_WhitespaceStripper.hpp 

filter_test_SOURCES = filter_test.cpp \
                      $(cppunit_sources) \
                      $(test_sources) 
filter_test_LDADD =  $(LIBARABICA)
filter_test_DEPENDENCIES = $(LIBARABICA)

filter_test_silly_SOURCES = filter_test_silly.cpp \
                      $(cppunit_sources) \
                      $(test_sources) \
                      $(silly_string_sources)
filter_test_silly_LDADD =  $(LIBARABICA)
filter_test_silly_DEPENDENCIES = $(LIBARABICA)

filter_test_wide_SOURCES = filter_test_wide.cpp \
                      $(cppunit_sources) \
                      $(test_sources) 
filter_test_wide_LDADD = $(LIBARABICA)
filter_test_wide_DEPENDENCIES = $(LIBARABICA)

test: $(noinst_PROGRAMS)
	@for p in $(noinst_PROGRAMS); do \
          echo Running $$p; \
          ./$$p -q; \
        done

