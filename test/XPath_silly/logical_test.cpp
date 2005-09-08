#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include "../silly_string/silly_string.hpp"
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
    XPathExpressionPtr<silly_string, silly_string_adaptor> orTest(new impl::OrOperator<silly_string, silly_string_adaptor>(new BoolValue<silly_string, silly_string_adaptor>(false), new BoolValue<silly_string, silly_string_adaptor>(false)));
    assertEquals(false, orTest->evaluateAsBool(dummy_));
  } // test1

  void test2()
  {
    XPathExpressionPtr<silly_string, silly_string_adaptor> orTest(new impl::OrOperator<silly_string, silly_string_adaptor>(new BoolValue<silly_string, silly_string_adaptor>(false), new BoolValue<silly_string, silly_string_adaptor>(true)));
    assertEquals(true, orTest->evaluateAsBool(dummy_));
  } // test2

  void test3()
  {
    XPathExpressionPtr<silly_string, silly_string_adaptor> orTest(new impl::OrOperator<silly_string, silly_string_adaptor>(new BoolValue<silly_string, silly_string_adaptor>(true), new BoolValue<silly_string, silly_string_adaptor>(false)));
    assertEquals(true, orTest->evaluateAsBool(dummy_));
  } // test3

  void test4()
  {
    XPathExpressionPtr<silly_string, silly_string_adaptor> orTest(new impl::OrOperator<silly_string, silly_string_adaptor>(new BoolValue<silly_string, silly_string_adaptor>(true), new BoolValue<silly_string, silly_string_adaptor>(true)));
    assertEquals(true, orTest->evaluateAsBool(dummy_));
  } // test4

  void test5()
  {
    XPathExpressionPtr<silly_string, silly_string_adaptor> andTest(new impl::AndOperator<silly_string, silly_string_adaptor>(new BoolValue<silly_string, silly_string_adaptor>(false), new BoolValue<silly_string, silly_string_adaptor>(false)));
    assertEquals(false, andTest->evaluateAsBool(dummy_));
  } // test5

  void test6()
  {
    XPathExpressionPtr<silly_string, silly_string_adaptor> andTest(new impl::AndOperator<silly_string, silly_string_adaptor>(new BoolValue<silly_string, silly_string_adaptor>(false), new BoolValue<silly_string, silly_string_adaptor>(true)));
    assertEquals(false, andTest->evaluateAsBool(dummy_));
  } // test6

  void test7()
  {
    XPathExpressionPtr<silly_string, silly_string_adaptor> andTest(new impl::AndOperator<silly_string, silly_string_adaptor>(new BoolValue<silly_string, silly_string_adaptor>(true), new BoolValue<silly_string, silly_string_adaptor>(false)));
    assertEquals(false, andTest->evaluateAsBool(dummy_));
  } // test7

  void test8()
  {
    XPathExpressionPtr<silly_string, silly_string_adaptor> andTest(new impl::AndOperator<silly_string, silly_string_adaptor>(new BoolValue<silly_string, silly_string_adaptor>(true), new BoolValue<silly_string, silly_string_adaptor>(true)));
    assertEquals(true, andTest->evaluateAsBool(dummy_));
  } // test8

private:
  DOM::Node<silly_string> dummy_;
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
