#ifndef ARABICA_DOM_TEST_SUITE_HPP
#define ARABICA_DOM_TEST_SUITE_HPP

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"

#include "test_DOMImplementation.hpp"
#include "test_DocumentType.hpp"
#include "test_Document.hpp"
#include "test_ProcessingInstruction.hpp"
#include "test_Siblings.hpp"
#include "test_Element.hpp"
#include "test_DocumentFragment.hpp"
#include "test_Attribute.hpp"
#include "test_Text.hpp"
#include "test_CDATA.hpp"
#include "test_CharacterData.hpp"
#include "test_SAX2DOM.hpp"
#include "test_TreeWalker.hpp"
#include "test_NamedNodeMap.hpp"
#include "test_Stream.hpp"

template<class string_type, class string_adaptor>
bool DOM_test_suite(int argc, const char** argv)
{
  TestRunner runner;

  runner.addTest("DOMImplementationTest", DOMImplementationTest_suite<string_type, string_adaptor >());
  runner.addTest("DocumentTypeTest", DocumentTypeTest_suite<string_type, string_adaptor >());
  runner.addTest("DocumentTest", DocumentTest_suite<string_type, string_adaptor >());
  runner.addTest("SiblingsTest", SiblingsTest_suite<string_type, string_adaptor >());
  runner.addTest("ElementTest", ElementTest_suite<string_type, string_adaptor >());
  runner.addTest("AttributeTest", AttrTest_suite<string_type, string_adaptor >());
  runner.addTest("ProcessingInstructionTest", ProcessingInstructionTest_suite<string_type, string_adaptor >());
  runner.addTest("TextTest", TextTest_suite<string_type, string_adaptor >());
  runner.addTest("CDATATest", CDATATest_suite<string_type, string_adaptor >());
  runner.addTest("CharacterDataText", CharacterDataTest_suite<string_type, string_adaptor >());
  runner.addTest("DocumentFragmentTest", DocumentFragmentTest_suite<string_type, string_adaptor >());
  runner.addTest("SAX2DOMTest", SAX2DOMTest_suite<string_type, string_adaptor>());
  runner.addTest("NamedNodeMapTest", NamedNodeMapTest_suite<string_type, string_adaptor>());
  runner.addTest("TreeWalkerTest", TreeWalkerTest_suite<string_type, string_adaptor>());
  runner.addTest("StreamTest", StreamTest_suite<string_type, string_adaptor>());
  
  return runner.run(argc, argv);
} // main

#endif

