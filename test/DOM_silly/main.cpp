#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include <iostream>
#include <string>

#include <iostream>
#include <vector>
#include <map>

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"

#include "../DOM/test_DOMImplementation.h"
#include "../DOM/test_DocumentType.h"
//#include "test_Document.h"
#include "../DOM/test_ProcessingInstruction.h"
//#include "test_Siblings.h"
//#include "test_Element.h"
//#include "test_DocumentFragment.h"
#include "../DOM/test_Attribute.h"
#include "../DOM/test_Text.hpp"
#include "../DOM/test_CDATA.hpp"
#include "../DOM/test_CharacterData.hpp"


#include "../silly_string/silly_string.hpp"

template<> class Arabica::default_string_adaptor<silly_string> : public silly_string_adaptor { };

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  TestRunner runner;

  runner.addTest("DOMImplementationTest", DOMImplementationTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("DocumentTypeTest", DocumentTypeTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  //runner.addTest("DocumentTest", DocumentTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  //runner.addTest("SiblingsTest", SiblingsTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  //runner.addTest("ElementTest", ElementTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("AttributeTest", AttrTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("ProcessingInstructionTest", ProcessingInstructionTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("TextTest", TextTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("CDATATest", CDATATest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("CharacterDataText", CharacterDataTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  //runner.addTest("DocumentFragmentTest", DocumentFragmentTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  
  runner.run(argc, argv);

  return 0;
} // main

// end of file
