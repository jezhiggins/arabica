#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"
#include <Utils/StringAdaptor.hpp>
#include "test_WhitespaceStripper.hpp"

////////////////////////////////////////////////
int main(int argc, const char* argv[])
{
  TestRunner runner;

  runner.addTest("WhitespaceStripperTest", WhitespaceStripper_test_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());

  runner.run(argc, argv);

  return 0;
} // main

