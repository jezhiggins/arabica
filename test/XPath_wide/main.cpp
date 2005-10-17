
#ifdef _MSC_VER
#pragma warning(disable:4224 4267)
#endif

#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/textui/TextTestResult.h"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"

#include "../XPath/value_test.hpp"
#include "../XPath/arithmetic_test.hpp"
#include "../XPath/relational_test.hpp"
#include "../XPath/logical_test.hpp"
#include "../XPath/axis_enumerator_test.hpp"
#include "../XPath/node_test_test.hpp"
#include "../XPath/step_test.hpp"
#include "../XPath/parse_test.hpp"
#include "../XPath/execute_test.hpp"

#include <string>

/////////////////////////////////////////
int main(int argc, char** argv)
{
  std::cout << "Hello" << std::endl;

  TestRunner runner;

  runner.addTest("ValueTest", ValueTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());
  runner.addTest("ArithmeticTest", ArithmeticTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());
  runner.addTest("RelationalTest", RelationalTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());
  runner.addTest("LogicalTest", LogicalTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());
  runner.addTest("AxisEnumeratorTest", AxisEnumeratorTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());
  runner.addTest("NodeTestTest", NodeTestTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());
  runner.addTest("StepTest", StepTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());
  runner.addTest("ParseTest", ParseTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());
  runner.addTest("ExecuteTest", ExecuteTest_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >());

  runner.run(argc, argv);
} // main

