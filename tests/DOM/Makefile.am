
check_PROGRAMS = dom_test dom_test_silly 
if HAS_STD_WSTRING
  check_PROGRAMS += dom_test_wide
endif
TESTS = $(check_PROGRAMS)

AM_CPPFLAGS = -I$(top_srcdir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA =  $(top_builddir)/src/libarabica.la
LIBSILLY = ../CppUnit/libsillystring.la
TESTLIBS = $(LIBARABICA) ../CppUnit/libcppunit.la

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
               test_Text.hpp \
               test_SAX2DOM.hpp \
               test_TreeWalker.hpp

dom_test_SOURCES = main.cpp \
                   $(test_sources)
dom_test_LDADD =  $(TESTLIBS)
dom_test_DEPENDENCIES = $(TESTLIBS)

dom_test_silly_SOURCES = main_silly.cpp \
                         $(test_sources) 
dom_test_silly_LDADD =  $(TESTLIBS) $(LIBSILLY)
dom_test_silly_DEPENDENCIES = $(TESTLIBS) $(LIBSILLY)

dom_test_wide_SOURCES = main_wide.cpp \
                        $(test_sources) 
dom_test_wide_LDADD =  $(TESTLIBS)
dom_test_wide_DEPENDENCIES = $(TESTLIBS)


