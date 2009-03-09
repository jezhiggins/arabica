#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"
#include <Arabica/StringAdaptor.hpp>
#include "test_Taggle.hpp"

////////////////////////////////////////////////
int main(int argc, const char* argv[])
{
  TestRunner runner;

  runner.addTest("TaggleTest", Taggle_test_suite());

  bool ok = runner.run(argc, argv);

  return !ok;
} // main

