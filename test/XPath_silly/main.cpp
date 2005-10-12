
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
#include "step_test.hpp"
#include "parse_test.hpp"
#include "execute_test.hpp"

#include "../silly_string/silly_string.hpp"

template<> class Arabica::default_string_adaptor<silly_string> : public silly_string_adaptor { };

/////////////////////////////////////////
int main(int argc, char** argv)
{
  std::cout << "Hello" << std::endl;

  TestRunner runner;

  runner.addTest("ValueTest", ValueTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("ArithmeticTest", ArithmeticTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("RelationalTest", RelationalTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("LogicalTest", LogicalTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("AxisEnumeratorTest", AxisEnumeratorTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("NodeTestTest", NodeTestTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("StepTest", StepTest_suite());
  runner.addTest("ParseTest", ParseTest_suite());
  runner.addTest("ExecuteTest", ExecuteTest_suite());

  runner.run(argc, argv);
} // main

