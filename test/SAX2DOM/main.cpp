#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include <iostream>
#include <string>
#include <DOM/SAX2DOM/SAX2DOM.h>

#include <iostream>
#include <vector>
#include <map>

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"

#include "test_SAX.h"
#include "../silly_string/silly_string.hpp"

////////////////////////////////////////////////
int main(int argc, const char* argv[])
{
  TestRunner runner;

  runner.addTest("SAX2DOMTest", SAXTest_suite<std::string, Arabica::default_string_adaptor<std::string> >());
  runner.addTest("SAX2DOMTest_silly", SAXTest_suite<silly_string, silly_string_adaptor>());
  runner.addTest("SAX2DOMTest_wide", SAXTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());

  runner.run(argc, argv);

  return 0;
} // main

// end of file
