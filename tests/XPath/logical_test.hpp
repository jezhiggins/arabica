#ifndef XPATHIC_LOGICAL_TEST_H
#define XPATHIC_LOGICAL_TEST_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>

template<class string_type, class string_adaptor>
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
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> orTest(new impl::OrOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(false)));
    assertEquals(false, orTest.evaluateAsBool(dummy_));
  } // test1

  void test2()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> orTest(new impl::OrOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(true)));
    assertEquals(true, orTest.evaluateAsBool(dummy_));
  } // test2

  void test3()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> orTest(new impl::OrOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(false)));
    assertEquals(true, orTest.evaluateAsBool(dummy_));
  } // test3

  void test4()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> orTest(new impl::OrOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(true)));
    assertEquals(true, orTest.evaluateAsBool(dummy_));
  } // test4

  void test5()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> andTest(new impl::AndOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(false)));
    assertEquals(false, andTest.evaluateAsBool(dummy_));
  } // test5

  void test6()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> andTest(new impl::AndOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(true)));
    assertEquals(false, andTest.evaluateAsBool(dummy_));
  } // test6

  void test7()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> andTest(new impl::AndOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(false)));
    assertEquals(false, andTest.evaluateAsBool(dummy_));
  } // test7

  void test8()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> andTest(new impl::AndOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(true)));
    assertEquals(true, andTest.evaluateAsBool(dummy_));
  } // test8

private:
  Arabica::DOM::Node<string_type, string_adaptor> dummy_;
}; // class LogicalTest

template<class string_type, class string_adaptor>
TestSuite* LogicalTest_suite()
{
  TestSuite* tests = new TestSuite;

  tests->addTest(new TestCaller<LogicalTest<string_type, string_adaptor> >("test1", &LogicalTest<string_type, string_adaptor>::test1));
  tests->addTest(new TestCaller<LogicalTest<string_type, string_adaptor> >("test2", &LogicalTest<string_type, string_adaptor>::test2));
  tests->addTest(new TestCaller<LogicalTest<string_type, string_adaptor> >("test3", &LogicalTest<string_type, string_adaptor>::test3));
  tests->addTest(new TestCaller<LogicalTest<string_type, string_adaptor> >("test4", &LogicalTest<string_type, string_adaptor>::test4));
  tests->addTest(new TestCaller<LogicalTest<string_type, string_adaptor> >("test5", &LogicalTest<string_type, string_adaptor>::test5));
  tests->addTest(new TestCaller<LogicalTest<string_type, string_adaptor> >("test6", &LogicalTest<string_type, string_adaptor>::test6));
  tests->addTest(new TestCaller<LogicalTest<string_type, string_adaptor> >("test7", &LogicalTest<string_type, string_adaptor>::test7));
  tests->addTest(new TestCaller<LogicalTest<string_type, string_adaptor> >("test8", &LogicalTest<string_type, string_adaptor>::test8));

  return tests;
} // LogicalTest_suite

#endif
