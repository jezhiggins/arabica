#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include <iostream>
#include <string>
//#include <wrappers/saxexpat.h>
#include <DOM/SAX2DOM/SAX2DOM.h>

#include <iostream>
#include <vector>
#include <map>

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
#include "test_SAX.h"
#include "test_Text.hpp"
#include "test_CDATA.hpp"
#include "test_CharacterData.hpp"

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  TestRunner runner;

  runner.addTest("DOMImplementationTest", DOMImplementationTest_suite<std::string, Arabica::default_string_adaptor_base<std::string> >());
  runner.addTest("DocumentTypeTest", DocumentTypeTest_suite<std::string, Arabica::default_string_adaptor_base<std::string> >());
  runner.addTest("DocumentTest", DocumentTest_suite());
  runner.addTest("SiblingsTest", SiblingsTest_suite());
  runner.addTest("ElementTest", ElementTest_suite());
  runner.addTest("AttributeTest", AttrTest_suite<std::string, Arabica::default_string_adaptor<std::string> >());
  runner.addTest("ProcessingInstructionTest", ProcessingInstructionTest_suite<std::string, Arabica::default_string_adaptor<std::string> >());
  runner.addTest("TextTest", TextTest_suite<std::string, Arabica::default_string_adaptor_base<std::string> >());
  runner.addTest("CDATATest", CDATATest_suite<std::string, Arabica::default_string_adaptor_base<std::string> >());
  runner.addTest("CharacterDataText", CharacterDataTest_suite<std::string, Arabica::default_string_adaptor_base<std::string> >());
  runner.addTest("DocumentFragmentTest", DocumentFragmentTest_suite());
  runner.addTest("SAX2DOMTest", SAXTest_suite());
  runner.run(argc, argv);

  return 0;
} // main

// end of file
