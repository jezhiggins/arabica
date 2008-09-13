#ifndef XPATHIC_XPATH_TEST_SUITE_HPP
#define XPATHIC_XPATH_TEST_SUITE_HPP

#include "../CppUnit/TestRunner.hpp"
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
#include "expression_test.hpp"
#include "match_test.hpp"
#include "attr_value_test.hpp"
#include "text_node_test.hpp"

template<class string_type, class string_adaptor>
bool XPath_test_suite(int argc, const char** argv)
{
  TestRunner runner;

  runner.addTest("ValueTest", ValueTest_suite<string_type, string_adaptor>());
  runner.addTest("ArithmeticTest", ArithmeticTest_suite<string_type, string_adaptor>());
  runner.addTest("RelationalTest", RelationalTest_suite<string_type, string_adaptor>());
  runner.addTest("LogicalTest", LogicalTest_suite<string_type, string_adaptor>());
  runner.addTest("AxisEnumeratorTest", AxisEnumeratorTest_suite<string_type, string_adaptor>());
  runner.addTest("NodeTestTest", NodeTestTest_suite<string_type, string_adaptor>());
  runner.addTest("StepTest", StepTest_suite<string_type, string_adaptor>());
  runner.addTest("ParseTest", ParseTest_suite<string_type, string_adaptor>());
  runner.addTest("ExecuteTest", ExecuteTest_suite<string_type, string_adaptor>());
  runner.addTest("ExpressionTest", ExpressionTest_suite<string_type, string_adaptor>());
  runner.addTest("MatchTest", MatchTest_suite<string_type, string_adaptor>());
  runner.addTest("AttributeValueTest", AttributeValueTest_suite<string_type, string_adaptor>());
  runner.addTest("TextNodeTest", TextNodeTest_suite<string_type, string_adaptor>());

  return runner.run(argc, argv);
} // XPath_test_suite

#endif
