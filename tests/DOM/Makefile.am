
check_PROGRAMS = dom_test dom_test_silly 
if HAS_STD_WSTRING
  check_PROGRAMS += dom_test_wide
endif
if WANT_TESTS
  TESTS = $(check_PROGRAMS)
endif


AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include @PARSER_HEADERS@ $(BOOST_CPPFLAGS)
LIBARABICA =  $(top_builddir)/src/libarabica.la
LIBSILLY = ../CppUnit/libsillystring.la
TESTLIBS = $(LIBARABICA) ../CppUnit/libcppunit.la

test_sources = dom_test_suite.hpp \
               test_Attribute.hpp \
               test_CDATA.hpp \
               test_CharacterData.hpp \
               test_DOMImplementation.hpp \
               test_Document.hpp \
               test_DocumentFragment.hpp \
               test_DocumentType.hpp \
               test_Element.hpp \
               test_NamedNodeMap.hpp \
               test_ProcessingInstruction.hpp \
               test_Siblings.hpp \
               test_Text.hpp \
               test_SAX2DOM.hpp \
               test_TreeWalker.hpp \
               test_Stream.hpp

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


