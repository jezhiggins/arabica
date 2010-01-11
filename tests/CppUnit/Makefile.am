
cppunit_sources = framework/CppUnitException.h \
                  framework/estring.h \
                  framework/Guards.h \
                  framework/Test.h \
                  framework/TestCaller.h \
                  framework/TestCase.cpp \
                  framework/TestCase.h \
                  framework/TestFailure.cpp \
                  framework/TestFailure.h \
                  framework/TestResult.cpp \
                  framework/TestResult.h \
                  framework/TestSuite.cpp \
                  framework/TestSuite.h \
                  TestRunner.cpp \
                  TestRunner.hpp \
                  textui/TextTestResult.cpp \
                  textui/TextTestResult.h \
                  textui/TableTestResult.cpp \
                  textui/TableTestResult.hpp \
                  textui/XmlTestResult.cpp \
                  textui/XmlTestResult.hpp 


silly_string_sources = ../silly_string/silly_string.cpp \
                       ../silly_string/silly_string.hpp

check_LTLIBRARIES = libcppunit.la libsillystring.la

libcppunit_la_SOURCES= $(cppunit_sources) 

libsillystring_la_SOURCES = $(silly_string_sources)
libsillystring_la_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include




