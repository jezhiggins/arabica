#ifndef ARABICA_DOM_TEST_SUITE_HPP
#define ARABICA_DOM_TEST_SUITE_HPP

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"

#include "test_DOMImplementation.h"
#include "test_DocumentType.h"
#include "test_Document.h"
#include "test_ProcessingInstruction.h"
#include "test_Siblings.h"
#include "test_Element.h"
#include "test_DocumentFragment.h"
#include "test_Attribute.h"
#include "test_Text.hpp"
#include "test_CDATA.hpp"
#include "test_CharacterData.hpp"

template<class string_type, class string_adaptor>
void DOM_test_suite(int argc, const char** argv)
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
  
  runner.run(argc, argv);
} // main

#endif

