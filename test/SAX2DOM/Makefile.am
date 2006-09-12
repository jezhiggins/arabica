
bin_PROGRAMS = sax2dom_test

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


test_sources = test_SAX.h

sax2dom_test_SOURCES = main.cpp $(cppunit_sources) $(test_sources) ../silly_string/silly_string.cpp ../silly_string/silly_string.hpp
sax2dom_test_DEPENDENCES = $(LIBARABICA)
sax2dom_test_LDADD =  $(LIBARABICA)

INCLUDES = -I$(top_srcdir)/include $(PARSER_HEADERS) $(BOOST_CPPFLAGS)

