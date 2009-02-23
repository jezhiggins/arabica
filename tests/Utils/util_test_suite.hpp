#ifndef ARABICA_UTIL_TEST_SUITE_HPP
#define ARABICA_UTIL_TEST_SUITE_HPP

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"

#include "test_normalize_whitespace.hpp"
#include "test_base64.hpp"
#include "test_uri.hpp"
#include "test_xml_strings.hpp"
#include "test_qname.hpp"

template<class string_type, class string_adaptor>
bool Util_test_suite(int argc, const char** argv)
{
  TestRunner runner;

  runner.addTest("NormalizeWhitespaceTest", NormalizeWhitespaceTest_suite<string_type, string_adaptor >());
  runner.addTest("Base64Test", Base64Test_suite());
  runner.addTest("URITest", URITest_suite());
  runner.addTest("XMLString", XMLStringTest_suite<string_type, string_adaptor>());
  runner.addTest("QualifiedName", QualifiedNameTest_suite<string_type, string_adaptor>());
  
  return runner.run(argc, argv);
} // main

#endif

