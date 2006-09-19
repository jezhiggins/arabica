
bin_PROGRAMS = dom_test dom_test_silly 
if HAS_STD_WSTRING
  bin_PROGRAMS += dom_test_wide
endif

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

test_sources = dom_test_suite.hpp \
                   test_Attribute.h \
                   test_CDATA.hpp \
                   test_CharacterData.hpp \
                   test_DOMImplementation.h \
                   test_Document.h \
                   test_DocumentFragment.h \
                   test_DocumentType.h \
                   test_Element.h \
                   test_ProcessingInstruction.h \
                   test_Siblings.h \
                   test_Text.hpp 

dom_test_SOURCES = main.cpp $(cppunit_sources) $(test_sources)
dom_test_DEPENDENCES = $(LIBARABICA)
dom_test_LDADD =  $(LIBARABICA)

dom_test_silly_SOURCES = main_silly.cpp $(cppunit_sources) $(test_sources) ../silly_string/silly_string.cpp ../silly_string/silly_string.hpp
dom_test_silly_DEPENDENCES = $(LIBARABICA)
dom_test_silly_LDADD =  $(LIBARABICA)

dom_test_wide_SOURCES = main_wide.cpp $(cppunit_sources) $(test_sources) 
dom_test_wide_DEPENDENCES = $(LIBARABICA)
dom_test_wide_LDADD =  $(LIBARABICA)


INCLUDES = -I$(top_srcdir)/include $(PARSER_HEADERS) $(BOOST_CPPFLAGS)

