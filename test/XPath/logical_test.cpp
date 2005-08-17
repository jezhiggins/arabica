#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>

using namespace Arabica::XPath;

class LogicalTest : public TestCase
{
public:
  LogicalTest(const std::string& name) : TestCase(name)
  {
  } // LogicalTest

  void setUp()
  {
  } // setUp

  void test1()
  {
    XPathExpressionPtr<std::string> orTest(new OrOperator<std::string, Arabica::default_string_adaptor<std::string> >(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    assertEquals(false, orTest->evaluateAsBool(dummy_));
  } // test1

  void test2()
  {
    XPathExpressionPtr<std::string> orTest(new OrOperator<std::string, Arabica::default_string_adaptor<std::string> >(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));
    assertEquals(true, orTest->evaluateAsBool(dummy_));
  } // test2

  void test3()
  {
    XPathExpressionPtr<std::string> orTest(new OrOperator<std::string, Arabica::default_string_adaptor<std::string> >(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    assertEquals(true, orTest->evaluateAsBool(dummy_));
  } // test3

  void test4()
  {
    XPathExpressionPtr<std::string> orTest(new OrOperator<std::string, Arabica::default_string_adaptor<std::string> >(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));
    assertEquals(true, orTest->evaluateAsBool(dummy_));
  } // test4

  void test5()
  {
    XPathExpressionPtr<std::string> andTest(new AndOperator<std::string, Arabica::default_string_adaptor<std::string> >(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    assertEquals(false, andTest->evaluateAsBool(dummy_));
  } // test5

  void test6()
  {
    XPathExpressionPtr<std::string> andTest(new AndOperator<std::string, Arabica::default_string_adaptor<std::string> >(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));
    assertEquals(false, andTest->evaluateAsBool(dummy_));
  } // test6

  void test7()
  {
    XPathExpressionPtr<std::string> andTest(new AndOperator<std::string, Arabica::default_string_adaptor<std::string> >(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    assertEquals(false, andTest->evaluateAsBool(dummy_));
  } // test7

  void test8()
  {
    XPathExpressionPtr<std::string> andTest(new AndOperator<std::string, Arabica::default_string_adaptor<std::string> >(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));
    assertEquals(true, andTest->evaluateAsBool(dummy_));
  } // test8

private:
  DOM::Node<std::string> dummy_;
}; // class LogicalTest

TestSuite* LogicalTest_suite()
{
  TestSuite* tests = new TestSuite;

  tests->addTest(new TestCaller<LogicalTest>("test1", &LogicalTest::test1));
  tests->addTest(new TestCaller<LogicalTest>("test2", &LogicalTest::test2));
  tests->addTest(new TestCaller<LogicalTest>("test3", &LogicalTest::test3));
  tests->addTest(new TestCaller<LogicalTest>("test4", &LogicalTest::test4));
  tests->addTest(new TestCaller<LogicalTest>("test5", &LogicalTest::test5));
  tests->addTest(new TestCaller<LogicalTest>("test6", &LogicalTest::test6));
  tests->addTest(new TestCaller<LogicalTest>("test7", &LogicalTest::test7));
  tests->addTest(new TestCaller<LogicalTest>("test8", &LogicalTest::test8));

  return tests;
} // LogicalTest_suite
