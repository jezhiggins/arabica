
#ifdef _MSC_VER
#pragma warning(disable:4224 4267)
#endif

#include "../CppUnit/TestRunner.hpp"
#include <iostream>
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"

#include "parse_test.hpp"
#include "value_test.hpp"
#include "arithmetic_test.hpp"
#include "relational_test.hpp"
#include "logical_test.hpp"
#include "axis_enumerator_test.hpp"
#include "node_test_test.hpp"
#include "step_test.hpp"
#include "execute_test.hpp"

/////////////////////////////////////////
int main(int argc, char** argv)
{
  std::cout << "Hello" << std::endl;

  TestRunner runner;

  runner.addTest("ValueTest", ValueTest_suite<std::string, Arabica::default_string_adaptor<std::string> >());
  runner.addTest("ArithmeticTest", ArithmeticTest_suite<std::string, Arabica::default_string_adaptor<std::string> >());
  runner.addTest("RelationalTest", RelationalTest_suite<std::string, Arabica::default_string_adaptor<std::string> >());
  runner.addTest("LogicalTest", LogicalTest_suite<std::string, Arabica::default_string_adaptor<std::string> >());
  runner.addTest("AxisEnumeratorTest", AxisEnumeratorTest_suite());
  runner.addTest("NodeTestTest", NodeTestTest_suite());
  runner.addTest("StepTest", StepTest_suite());
  runner.addTest("ParseTest", ParseTest_suite());
  runner.addTest("ExecuteTest", ExecuteTest_suite());

  runner.run(argc, argv);
} // main

